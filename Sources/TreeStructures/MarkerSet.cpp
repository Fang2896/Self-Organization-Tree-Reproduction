//
// Created by fangl on 2023/8/19.
//

#include <algorithm>

#include "MarkerSet.h"


void Marker::resetAllocation() {
    allocationId = 0;
    distanceToAllocated = std::numeric_limits<float>::infinity();
}


// constructor
MarkerSet::MarkerSet(QRandomGenerator &randomGenerator, float sideLength, U64 resolution, U64 pointCount)
    : xRange(-0.5f * sideLength, 0.5 * sideLength),
      yRange(0.0f, sideLength),
      zRange(-0.5f * sideLength, 0.5 * sideLength),
      resolution(resolution)
{
    if (sideLength <= 0.0f) {
        throw std::domain_error("Error: Side length cannot be <= 0.0f.");
    }
    if (resolution < 1) {
        throw std::domain_error("Error: Resolution must be at least 1.");
    }
    const auto boxNum = resolution * resolution * resolution;
    if (pointCount % boxNum != 0) {
        throw std::domain_error("Error: Point count should be evenly divisible between the boxes.");
    }

    const auto pointsPerBox = pointCount / boxNum;
    for(U64 x = 0; x < resolution; x++) {
        markers.emplace_back();
        const auto xRangeMin = xRange.interpolate(x, resolution);
        const auto xRangeMax = xRange.interpolate(x + 1, resolution);

        for (U64 y = 0; y < resolution; y++) {
            markers[x].emplace_back();
            const auto yRangeMin = yRange.interpolate(y, resolution);
            const auto yRangeMax = yRange.interpolate(y + 1, resolution);

            for (U64 z = 0; z < resolution; z++) {
                markers[x][y].emplace_back();
                const auto zRangeMin = zRange.interpolate(z, resolution);
                const auto zRangeMax = zRange.interpolate(z + 1, resolution);

                for (U64 i = 0; i < pointsPerBox; i++) {
                    // randomly scatter marker points in single box
                    markers[x][y][z].emplace_back();
                    markers[x][y][z][i].position.setX(randomGenerator.bounded(xRangeMax - xRangeMin) + xRangeMin);
                    markers[x][y][z][i].position.setY(randomGenerator.bounded(yRangeMax - yRangeMin) + yRangeMin);
                    markers[x][y][z][i].position.setZ(randomGenerator.bounded(zRangeMax - zRangeMin) + zRangeMin);
                }
            }
        }
    }
}

void MarkerSet::resetAllocations() {
    for (auto &xVec : markers) {
        for (auto &xyVec : xVec) {
            for (auto &xyzVec : xyVec) {
                for (auto &marker : xyzVec) {
                    marker.resetAllocation();
                }
            }
        }
    }
}

// space colonization algorithms:
void MarkerSet::updateAllocatedInCone(BudId budId, Point origin, Vector direction, float theta, float r) {
    const auto ranges = getBoxRangesForSphere(origin, r);
    for (auto x = ranges.minX; x < ranges.maxX; x++) {
        for (auto y = ranges.minY; y < ranges.maxY; y++) {
            for (auto z = ranges.minZ; z < ranges.maxZ; z++) {
                for (auto &marker : markers[x][y][z]) {
                    const auto point = marker.position;
                    const auto distanceFromBud = point.distanceToPoint(origin);
                    // Is it outside the distance or Is it no less than the current allocated distance?
                    if(distanceFromBud >= r || distanceFromBud >= marker.distanceToAllocated)
                        continue;

                    // Is within angle?
                    if (Vector(origin, point).angleBetween(direction) < theta) {  // BUG: 这里应该同时更新距离
                        marker.allocationId = budId;
                        marker.distanceToAllocated = distanceFromBud;
                    }
                }
            }
        }
    }
}

// get growth direction
SpaceAnalyst MarkerSet::getAllocatedInCone(BudId budId, Point origin, Vector direction, float theta, float r) const {
    Vector sumOfNormalizedVectors{};
    auto foundMarker = false;   // for Q
    const auto ranges = getBoxRangesForSphere(origin, r);
    for (auto x = ranges.minX; x < ranges.maxX; x++) {
        for (auto y = ranges.minY; y < ranges.maxY; y++) {
            for (auto z = ranges.minZ; z < ranges.maxZ; z++) {
                for (const auto &marker : markers[x][y][z]) {
                    const auto point = marker.position;
                    if (marker.allocationId != budId || point.distanceToPoint(origin) >= r)
                        continue;

                    // Is within angle?
                    if (Vector(origin, point).angleBetween(direction) < theta) {
                        foundMarker = true; // allow growing branch
                        sumOfNormalizedVectors = sumOfNormalizedVectors.add(Vector(origin, point).normalized());
                    }
                }
            }
        }
    }

    SpaceAnalyst spaceAnalysis{};
    if (foundMarker) {
        spaceAnalysis.q = 1.0f;
        spaceAnalysis.v = sumOfNormalizedVectors.normalized();
    }

    return spaceAnalysis;
}

void MarkerSet::removeMarkersInSphere(Point center, float radius) {
    const auto ranges = getBoxRangesForSphere(center, radius);
    for (auto x = ranges.minX; x < ranges.maxX; x++) {
        for (auto y = ranges.minY; y < ranges.maxY; y++) {
            for (auto z = ranges.minZ; z < ranges.maxZ; z++) {
                auto &xyzVector = markers[x][y][z];
                const auto predicate = [center, radius](Marker &marker) { return marker.position.distanceToPoint(center) < radius; };
                xyzVector.erase(std::remove_if(std::begin(xyzVector), std::end(xyzVector), predicate), std::end(xyzVector));
            }
        }
    }
}

BoxRanges MarkerSet::getBoxRangesForSphere(Point origin, float radius) const {
    BoxRanges ranges;
    const auto xIndexRange = BaseAlgorithms::getResRangeInRadius(xRange, resolution, origin.x(), radius);
    ranges.minX = static_cast<U64>(xIndexRange.minimum);
    ranges.maxX = static_cast<U64>(xIndexRange.maximum);
    const auto yIndexRange = BaseAlgorithms::getResRangeInRadius(yRange, resolution, origin.y(), radius);
    ranges.minY = static_cast<U64>(yIndexRange.minimum);
    ranges.maxY = static_cast<U64>(yIndexRange.maximum);
    const auto zIndexRange = BaseAlgorithms::getResRangeInRadius(zRange, resolution, origin.z(), radius);
    ranges.minZ = static_cast<U64>(zIndexRange.minimum);
    ranges.maxZ = static_cast<U64>(zIndexRange.maximum);
    return ranges;
}
