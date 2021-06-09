#pragma once

#include "Point.h"
#include "../r-tree/prism.h"
#include <iostream>
#include <cmath>

using namespace std;

struct Triangle {
    Point *firstVertex;
    Point *secondVertex;
    Point *thirdVertex;
};

class Vector3 {
    double xCoord;
    double yCoord;
    double zCoord;
public:
    Vector3(double x, double y, double z);

    Vector3(const Point &start, const Point &end);

    static double dot(const Vector3 &v1, const Vector3 &v2);

    static Vector3 cross(const Vector3 &v1, const Vector3 &v2);

    double Length() const;
};

struct Line {
    Point *p1;
    Point *p2; // actually, it isn't a real second point, it's a vector

    double triangle_intersection(const Triangle &triangle) const;

    Point intersectionWithTriangle(const Triangle &triangle);

    Point locationWhenX(double x);

    Point locationWhenY(double y);

    Point locationWhenZ(double z);

    bool doesIntersectParallelepiped(const Prism &prism);
};