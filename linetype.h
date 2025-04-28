// lineType.h
#ifndef LINETYPE_H
#define LINETYPE_H

struct Point {
    double x;
    double y;
};

class lineType {
private:
    double a, b, c;

public:
    lineType();
    lineType(double, double, double);

    double getSlope() const;
    bool isVertical() const;
    bool isHorizontal() const;
    bool isParallel(const lineType&) const;
    bool isPerpendicular(const lineType&) const;
    bool intersectionPoint(const lineType&, Point&) const;
};

#endif
