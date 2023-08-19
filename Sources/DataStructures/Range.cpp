//
// Created by fangl on 2023/8/19.
//

#include "Range.h"


Range Range::merge(Range other) const
{
    const auto min = std::min(minimum, other.minimum);
    const auto max = std::max(maximum, other.maximum);

    return {min, max};
}

float Range::interpolate(U64 value, U64 resolution) const
{
    if(value > resolution) {
        throw std::domain_error("Value Error: Value is larger than resolution.");
    }
    const auto factor = static_cast<float>(value) / static_cast<float>(resolution);
    return minimum + factor * (maximum - minimum);
}

float Range::getMidValue() const {
    return 0.5f * (maximum + minimum);
}

float Range::getLength() const {
    return maximum - minimum;
}
