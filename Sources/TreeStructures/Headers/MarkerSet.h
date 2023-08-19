//
// Created by fangl on 2023/8/19.
//

#ifndef MARKERSET_H
#define MARKERSET_H

#include <vector>
#include <stdexcept>

#include <QVector>
#include <QRandomGenerator>

#include "Types.h"
#include "Range.h"
#include "Vector.h"
#include "BoundingBox.h"
#include "BaseAlgorithms.h"

class Marker;
class BoxRanges;
class SpaceAnalyst;

class MarkerSet
{
public:
    Range xRange;
    Range yRange;
    Range zRange;

    U64 resolution;
    std::vector<std::vector<std::vector<std::vector<Marker>>>> markers;

    MarkerSet(QRandomGenerator &randomGenerator,
              float sideLength, U64 resolution, U64 pointCount);

    void resetAllocations();

    // paper algorithms
    void updateAllocatedInCone(BudId budId, Point origin, Vector direction,
                               float theta, float r);
    SpaceAnalyst getAllocatedInCone(BudId budId, Point origin, Vector direction,
                                    float theta, float r) const;
    void removeMarkersInSphere(Point center, float radius);

private:
    BoxRanges getBoxRangesForSphere(Point origin, float radius) const;

};


class Marker
{
public:
    Point position{};
    U64 allocationId{}; // record its belong to which bud
    float distanceToAllocated = std::numeric_limits<float>::infinity();

    void resetAllocation();
};

class BoxRanges
{
public:
    U64 minX{};
    U64 maxX{};
    U64 minY{};
    U64 maxY{};
    U64 minZ{};
    U64 maxZ{};
};


// used to calculate growth direction
class SpaceAnalyst
{
public:
    F32 q{};
    Vector v{};

};


#endif //MARKERSET_H
