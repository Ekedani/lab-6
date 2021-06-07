#pragma once
#include "../data-struct/Point.h"

class Prism {
private:
    Point *firstPoint;

    Point *secondPoint;

public:
    Prism();

    Prism(Point *p1, Point *p2);

    Prism(const Prism &prism);

    Prism &operator=(const Prism &prism);

    bool isInside(const Point &point) const;

    double volume() const;

    Prism Intersection(const Prism &prism);

    double overlapVolume(const Prism &prism);

    void reorder();

    Prism extend(const Point &point);

    double volumeIncreasing(const Point &point);

    double volumeIncreasing(const Prism &prism);

    Point *getFirstPoint() const;

    Point *getSecondPoint() const;
};
