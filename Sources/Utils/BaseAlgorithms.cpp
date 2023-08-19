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

Vector BaseAlgorithms::randomPerturbation(QRandomGenerator &randomGenerator, Vector originalVector, float angle) {
    Vector vx(1.0f, 0.0f, 0.0f);
    Vector vy(0.0f, 1.0f, 0.0f);
    Vector auxiliaryVector = vx;
    // 防止辅助向量与originalVector接近共线
    if (std::abs(originalVector.dot(vx)) > (1.0f - 1.0e-6f)) {
        auxiliaryVector = vy;
    }
    const auto crossVector = originalVector.cross(auxiliaryVector).normalized();
    const auto s = randomGenerator.generateDouble();
    const auto r = randomGenerator.generateDouble();
    const auto h = std::cos(angle);
    const auto phi = 2.0f * 4.0f * std::atan(1.0f) * s;
    const auto z = h + (1.0f - h) * r;
    const auto sinOfT = std::sqrt(1.0f - z * z);
    const auto x = std::cos(phi) * sinOfT;
    const auto y = std::sin(phi) * sinOfT;
    return auxiliaryVector.scale(x).add(crossVector.scale(y)).add(originalVector.scale(z));
}


