//
// Created by fangl on 2023/8/19.
//

#include "Tree.h"

#include <QDebug>


Tree::Tree(Environment &environment, Point seedlingPosition)
    : environment(environment) {
    const auto end = seedlingPosition + Point(0.0f, 1.0f * Environment::MetamerBaseLength, 0.0f);
    root = std::make_unique<Metamer>(environment, seedlingPosition, end);
}

U64 Tree::countMetamers() const {
    if (!root)
        return 0;
    return root->countMetamers();
}

BoundingBox Tree::getBoundingBox() const {
    return root->getBoundingBox();
}

void Tree::performGrowthIteration() {
    // 1. Calculate local environment of all tree buds.
    //  generate markerSets for every iteration
    environment.markerSet.resetAllocations();
    allocateMarkers(root);
    // 2. Determine the fate of each bud (the extended Borchert-Honda model).
    propagateLightBasipetally(root);
    root->growthResource = Environment::BorchertHondaAlpha * root->light;
    propagateResourcesAcropetally(root);
    // 3. Append new shoots.
    performGrowthIteration(root);
    // 4. Shed branches (not implemented).

    // 5. Update internode width for all inter nodes.
    updateInternodeWidths(root);
    tropismGrowthDirectionWeight *= tropismGrowthDirectionWeightAttenuation;

    qDebug() << "Completed Iteration " << Qt::endl;
}

void Tree::allocateMarkers(std::unique_ptr<Metamer> &metamer) {
    if (!metamer)
        return;

    const auto theta = Environment::PerceptionAngle;
    const auto r = Environment::PerceptionRadiusFactor * metamer->getLength();

    if (!metamer->axillary) {
        environment.markerSet.updateAllocatedInCone(metamer->axillaryId, metamer->end, metamer->axillaryDirection, theta, r);
    } else {
        allocateMarkers(metamer->axillary);
    }

    if (!metamer->terminal) {
        // 这里可以根据不同的环境来修改terminal bud的方向
        const auto direction = Vector(metamer->begin, metamer->end);
        environment.markerSet.updateAllocatedInCone(metamer->terminalId, metamer->end, direction, theta, r);
    } else {
        allocateMarkers(metamer->terminal);
    }
}

/*********** Update Parameters Member Functions ***********/
// Light value
void Tree::propagateLightBasipetally(std::unique_ptr<Metamer> &metamer) {
    if (!metamer)
        return;

    propagateLightBasipetally(metamer->axillary);
    propagateLightBasipetally(metamer->terminal);
    const auto theta = Environment::PerceptionAngle;
    const auto r = Environment::PerceptionRadiusFactor * metamer->getLength();
    metamer->light = 0.0f;

    // 如果有芽，则通过计算marker的有无，来计算Q，也就是光量，若无芽只有metamer，只需要累加子枝的光量即可
    if (!metamer->axillary) {
        const auto budId = metamer->axillaryId;
        metamer->axillaryLight = environment.markerSet.getAllocatedInCone(budId, metamer->end, metamer->axillaryDirection, theta, r).q;
    } else {
        metamer->axillaryLight = metamer->axillary->light;
    }

    if (!metamer->terminal) {
        const auto direction = Vector(metamer->begin, metamer->end);
        const auto budId = metamer->terminalId;
        metamer->terminalLight = environment.markerSet.getAllocatedInCone(budId, metamer->end, direction, theta, r).q;
    } else {
        metamer->terminalLight = metamer->terminal->light;
    }

    metamer->light = metamer->axillaryLight + metamer->terminalLight;
}

// Resource value
void Tree::propagateResourcesAcropetally(std::unique_ptr<Metamer> &metamer) {
    if (!metamer)
        return;

    const auto qM = metamer->terminalLight;
    const auto qL = metamer->axillaryLight;
    if (qM + qL == 0.0f)
        return;

    const auto v = metamer->growthResource;
    const auto lambda = Environment::BorchertHondaLambda;
    const auto denominator = lambda * qM + (1.0f - lambda) * qL;
    const auto vM = v * (lambda * qM) / denominator;
    const auto vL = v * ((1.0f - lambda) * qL) / denominator;
    if (metamer->axillary) {
        metamer->axillary->growthResource = vL;
        metamer->axillaryGrowthResource = 0.0f; // 已经传上侧芽了，所以已经没了
        propagateResourcesAcropetally(metamer->axillary);
    } else {
        metamer->axillaryGrowthResource = vL; // 没有侧芽就自己留着
    }
    if (metamer->terminal) {
        metamer->terminal->growthResource = vM;
        metamer->terminalGrowthResource = 0.0f;
        propagateResourcesAcropetally(metamer->terminal);
    } else {
        metamer->terminalGrowthResource = vM;
    }
    // 此时资源在terminalGrowthResource或者axillaryGrowthResource上
    // 或者已经传递给下一个了
    // 故要清空
    metamer->growthResource = 0.0f;
}

// Core Growth Function
void Tree::performGrowthIteration(std::unique_ptr<Metamer> &metamer) {
    if (!metamer)
        return;

    if (!metamer->axillary) {
        metamer->axillary = addNewShoot(metamer->axillaryId, metamer->getLength(), metamer->end, metamer->axillaryDirection, metamer->axillaryGrowthResource);
    } else {
        performGrowthIteration(metamer->axillary);
    }
    if (!metamer->terminal) {
        const auto direction = Vector(metamer->begin, metamer->end);
        metamer->terminal = addNewShoot(metamer->terminalId, metamer->getLength(), metamer->end, direction, metamer->terminalGrowthResource);
    } else {
        performGrowthIteration(metamer->terminal);
    }
}

// Grow Branch Functions
std::unique_ptr<Metamer> Tree::addNewShoot(BudId budId, float supportingMetamerLength, Point origin, Vector direction, float resource) {
    const auto theta = Environment::PerceptionAngle;
    const auto r = Environment::PerceptionRadiusFactor * supportingMetamerLength;
    const auto spaceAnalysis = environment.markerSet.getAllocatedInCone(budId, origin, direction, theta, r);
    if (spaceAnalysis.q == 0.0f || std::floor(resource) == 0.0f)
        return nullptr;

    std::unique_ptr<Metamer> headMetamer;
    std::unique_ptr<Metamer> *nextMetamer = &headMetamer;
    auto metamerEnd = origin;
    auto metamerDirection = direction;
    const auto optimalGrowthDirection = spaceAnalysis.v.normalized();
    // 可以考虑设置为世界光照方向？或者其他影响因素
    const auto tropismDirection = Vector(0.0f, 1.0f, 0.0f).normalized();

    // 论文计算新metamer的个数以及长度公式
    const auto metamerLength = resource / static_cast<int>(std::floor(resource)) * Environment::MetamerBaseLength;
    for (auto metamers = static_cast<int>(std::floor(resource)); metamers > 0; metamers--) {
        metamerDirection = metamerDirection.add(optimalGrowthDirection.scale(Environment::OptimalGrowthDirectionWeight));
        metamerDirection = metamerDirection.add(tropismDirection.scale(tropismGrowthDirectionWeight));
        metamerDirection = metamerDirection.normalized();

        const auto metamerVector = metamerDirection.scale(metamerLength);
        const auto previousMetamerEnd = metamerEnd;

        metamerEnd = metamerEnd + Point(metamerVector.x(), metamerVector.y(), metamerVector.z());

        // TODO: here to remove Markers in Sphere range
        environment.markerSet.removeMarkersInSphere(metamerEnd, Environment::OccupancyRadiusFactor * metamerLength);

        *nextMetamer = std::make_unique<Metamer>(environment, previousMetamerEnd, metamerEnd);
        nextMetamer = &(*nextMetamer)->terminal;
    }

    return headMetamer;
}

// Equation: d^n = d1^n + d2^n
void Tree::updateInternodeWidths(std::unique_ptr<Metamer> &metamer) {
    if (!metamer) {
        return;
    }
    auto total = pipeModelLeafValue;
    updateInternodeWidths(metamer->axillary);
    if (metamer->axillary) {
        total += std::pow(metamer->axillary->width, pipeModelExponent);
    }
    updateInternodeWidths(metamer->terminal);
    if (metamer->terminal) {
        total += std::pow(metamer->terminal->width, pipeModelExponent);
    }
    metamer->width = std::pow(total, 1.0f / pipeModelExponent);
}

