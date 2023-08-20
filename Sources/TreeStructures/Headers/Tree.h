//
// Created by fangl on 2023/8/19.
//

#ifndef TREE_H
#define TREE_H

#include <memory>

#include "Types.h"
#include "Vector.h"
#include "Metamer.h"
#include "BoundingBox.h"
#include "Environment.h"


class Tree
{
public:
    std::unique_ptr<Metamer> root;
    Environment &environment;

    // Tree Parameters
    float tropismGrowthDirectionWeight = 0.5f;
    float tropismGrowthDirectionWeightAttenuation = 0.95f;
    float pipeModelExponent = 2.0f;  // 宽度公式中的n： d^n = d1^n + d2^n，
    float pipeModelLeafValue = 1.0e-8f;  // 叶子茎的宽度

    Tree(Environment &env, Point seedlingPosition);

    U64 countMetamers() const;
    void printAllMetamer(std::unique_ptr<Metamer> &metamer) const;
    BoundingBox getBoundingBox() const;

    void performGrowthIteration();
    void resetGrowth();

private:
    void allocateMarkers(std::unique_ptr<Metamer> &metamer);
    void propagateLightBasipetally(std::unique_ptr<Metamer> &metamer);
    void propagateResourcesAcropetally(std::unique_ptr<Metamer> &metamer);
    void performGrowthIteration(std::unique_ptr<Metamer> &metamer);
    std::unique_ptr<Metamer> addNewShoot(BudId budId, float supportingMetamerLength,
                                         Point origin, Vector direction, float resource);
    void updateInternodeWidths(std::unique_ptr<Metamer> &metamer);
};


#endif //TREE_H
