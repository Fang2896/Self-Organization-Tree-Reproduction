//
// Created by fangl on 2023/8/19.
//

#ifndef RANGE_H
#define RANGE_H

#include <limits>
#include <cstdint>
#include <algorithm>
#include <stdexcept>

#include "Types.h"


class Range
{
public:
    float minimum = std::numeric_limits<float>::max();
    float maximum = std::numeric_limits<float>::min();

    Range() = default;
    Range(float min, float max) : minimum(min), maximum(max) {}

    Range merge(Range other) const;
    float interpolate(U64 value, U64 resolution) const;
    float getMidValue() const;
    float getLength() const;

};





#endif //RANGE_H
