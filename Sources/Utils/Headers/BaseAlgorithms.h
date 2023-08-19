//
// Created by fangl on 2023/8/19.
//

#ifndef BASEALGORITHMS_H
#define BASEALGORITHMS_H

#include "Types.h"
#include "Range.h"
#include "Vector.h"
#include "BoundingBox.h"


class BaseAlgorithms
{
public:
    static float clampFloat(const float& value, const float& low, const float& high);
    static Range getResRangeInRadius(Range range, float resolution, float x, float radius);

private:
    BaseAlgorithms() {}
};


#endif //BASEALGORITHMS_H
