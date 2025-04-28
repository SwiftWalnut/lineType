// lineType.cpp
#include "lineType.h"
#include <iostream>
#include <cmath>

lineType::lineType() {
    a = 0;
    b = 0;
    c = 0;
}

lineType::lineType(double coefA, double coefB, double coefC) {
    a = coefA;
    b = coefB;
    c = coefC;
}

double lineType::getSlope() const {
    if (b == 0) {
        throw std::runtime_error("Vertical line - slope undefined");
    }
    return -a / b;
}

bool lineType::isVertical() const {
    return b == 0;
}

bool lineType::isHorizontal() const {
    return a == 0;
}

bool lineType::isParallel(const lineType& other) const {
    if (this->isVertical() && other.isVertical())
        return true;
    if (this->isVertical() || other.isVertical())
        return false;
    return std::abs(this->getSlope() - other.getSlope()) < 1e-6;
}

bool lineType::isPerpendicular(const lineType& other) const {
    if ((this->isVertical() && other.isHorizontal()) || (this->isHorizontal() && other.isVertical()))
        return true;
    if (this->isVertical() || other.isVertical())
        return false;
    return std::abs(this->getSlope() * other.getSlope() + 1) < 1e-6;
}

bool lineType::intersectionPoint(const lineType& other, Point& p) const {
    double determinant = a * other.b - other.a * b;

    if (std::abs(determinant) < 1e-6) {
        // Lines are parallel, no intersection
        return false;
    }

    p.x = (c * other.b - other.c * b) / determinant;
    p.y = (a * other.c - other.a * c) / determinant;
    return true;
}
