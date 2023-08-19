//
// Created by fangl on 2023/8/19.
//

#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

#include "Types.h"


class Vector
{
public:
    Vector() = default;
    Vector(QVector3D vec);
    Vector(Point a, Point b);
    Vector(float x, float y, float z);

    float x() const;
    float y() const;
    float z() const;

    void setX(float value);
    void setY(float value);
    void setZ(float value);

    float evaluateNorm() const;
    void normalize();
    Vector normalized() const;
    Vector scale(float factor) const;
    Vector add(Vector vec) const;
    float dot(Vector vec) const;
    float angleBetween(Vector vec) const;
    Vector cross(Vector other) const;

private:
    QVector3D vector;

};


#endif //VECTOR_H
