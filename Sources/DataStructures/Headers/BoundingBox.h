//
// Created by fangl on 2023/8/19.
//

#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <string>
#include <limits>
#include <sstream>
#include <algorithm>

#include "Range.h"
#include "Vector.h"


class BoundingBox
{
public:
    Range xRange;
    Range yRange;
    Range zRange;

    BoundingBox() = default;
    explicit BoundingBox(const std::string &string);
    BoundingBox(const Range &xR, const Range &yR, const Range &zR);

    void include(Point point);
    BoundingBox merge(BoundingBox other) const;
    std::string toString() const;

};


#endif //BOUNDINGBOX_H
