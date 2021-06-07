#include "../data-struct/triangle.h"
#include <algorithm>

class Prism {
private:
    Point *firstPoint;

    Point *secondPoint;

public:
    Prism();

    Prism(Point *p1, Point *p2);

    Prism(const Prism &prism);

    Prism &operator=(const Prism &prism);

    double volume() const;

    Prism Intersection(const Prism &prism);

    double overlapVolume(const Prism &prism);

    Prism extend(const Point &point);

    double volumeIncreasing(const Point &point);

    double volumeIncreasing(const Prism &prism);

    Point *getFirstPoint() const;

    Point *getSecondPoint() const;
};
