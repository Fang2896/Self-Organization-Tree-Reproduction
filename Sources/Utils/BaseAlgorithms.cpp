//
// Created by fangl on 2023/8/19.
//

#include "Headers/BaseAlgorithms.h"


float BaseAlgorithms::clampFloat(const float& value, const float& low, const float& high) {
    assert(!(high < low));
    if (value < low) return low;
    else if (high < value) return high;
    else return value;
}

Range BaseAlgorithms::getResRangeInRadius(Range range, float resolution, float x, float radius) {
    const auto minimum = range.minimum;
    const auto maximum = range.maximum;
    const auto step = (maximum - minimum) / resolution;
    const auto low  = clampFloat(std::floor((x - radius - minimum) / step), 0.0f, resolution);
    const auto high = clampFloat(std::ceil((x + radius - minimum) / step), 0.0f, resolution);
    return {low, high}; // 无小数的浮点数
}
