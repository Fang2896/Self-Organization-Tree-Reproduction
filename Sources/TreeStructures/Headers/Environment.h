//
// Created by fangl on 2023/8/19.
//

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Types.h"
#include "MarkerSet.h"


class Environment {
private:
    BudId nextBudId = 1;

public:
    static constexpr auto Pi = 3.1415926535897932384626433832795f;

    // In meters.
    static constexpr auto MetamerBaseLength = 0.01f;    // metamer的基础长度（权重）

    static constexpr auto OccupancyRadiusFactor = 2.0f;   // 占领区的半径
    static constexpr auto PerceptionRadiusFactor = 4.0f;  // 感知区的半径

    static constexpr auto PerceptionAngle = Pi / 2.0f;    // 感知角度，90度

    static constexpr auto AxillaryPerturbationAngle = Pi / 9.0f; // 随机扰动角度

    static constexpr auto BorchertHondaAlpha = 2.0f;    // 光合作用强度，根收到的光与往上传的资源成正比
    static constexpr auto BorchertHondaLambda = 0.5f;   // 论文中的λ，用来计算资源在枝条分叉区计算分配比率

    static constexpr auto OptimalGrowthDirectionWeight = 0.2f;  // 论文中的ξ，是V的权重

    QRandomGenerator randomGenerator;
    MarkerSet markerSet;

    Environment(const QRandomGenerator &rGenerator, MarkerSet markerSet)
        : randomGenerator(rGenerator), markerSet(std::move(markerSet)) {}

    BudId getNextBudId() {
        const auto value = nextBudId;
        nextBudId++;
        return value;
    }

    void resetEnvironment(const QRandomGenerator& rGenerator) {
        randomGenerator = rGenerator;
        nextBudId = 1;
    }
};


#endif //ENVIRONMENT_H
