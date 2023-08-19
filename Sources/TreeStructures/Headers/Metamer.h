//
// Created by fangl on 2023/8/19.
//

#ifndef METAMER_H
#define METAMER_H

#include <memory>

#include "Vector.h"
#include "BaseAlgorithms.h"
#include "BoundingBox.h"
#include "Environment.h"


class Metamer
{
public:
    Point begin{};
    Point end{};

    Vector axillaryDirection;

    bool hasLeaf = false;
    float width = 0.0f;

    std::unique_ptr<Metamer> axillary;
    BudId axillaryId{};

    std::unique_ptr<Metamer> terminal;
    BudId terminalId{};

    float light = 0.0f;

    float axillaryLight = 0.0f;
    float terminalLight = 0.0f;

    float growthResource = 0.0f;

    float axillaryGrowthResource = 0.0f;
    float terminalGrowthResource = 0.0f;

    Metamer(Environment &environment, const Point &begin, const Point &end);

    Point getCenter() const;
    float getLength() const;
    U64 countMetamers() const;
    BoundingBox getBoundingBox() const;
};


#endif //METAMER_H
