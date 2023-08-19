//
// Created by fangl on 2023/8/19.
//

#include "Vector.h"


float Vector::x() const {
    return this->vector.x();
}

float Vector::y() const {
    return this->vector.y();
}

float Vector::z() const {
    return this->vector.z();
}

void Vector::setX(float value) {
    this->vector.setX(value);
}

void Vector::setY(float value) {
    this->vector.setY(value);
}

void Vector::setZ(float value) {
    this->vector.setZ(value);
}

Vector::Vector(QVector3D vector) {
    this->vector = vector;
}

Vector::Vector(Point a, Point b) {
    this->vector = b - a;
}

Vector::Vector(float x, float y, float z) {
    this->vector.setX(x);
    this->vector.setY(y);
    this->vector.setZ(z);
}

float Vector::evaluateNorm() const {
    return this->vector.length();
}

void Vector::normalize() {
    this->vector.normalize();
}

Vector Vector::normalized() const {
    return this->vector.normalized();
}

Vector Vector::scale(float factor) const {
    return vector * factor;
}

Vector Vector::add(Vector other) const {
    return {vector.x() + other.x(), vector.y() + other.y(), vector.z() + other.z()};
}

float Vector::dot(Vector other) const {
    return vector.x() * other.x() + vector.y() * other.y() + vector.z() * other.z();
}

float Vector::angleBetween(Vector other) const {
    return std::acos(dot(other) / evaluateNorm() / other.evaluateNorm());
}

Vector Vector::cross(Vector other) const {
    const auto cx = vector.y() * other.z() - vector.z() * other.y();
    const auto cy = vector.z() * other.x() - vector.x() * other.z();
    const auto cz = vector.x() * other.y() - vector.y() * other.x();
    return {cx, cy, cz};
}
