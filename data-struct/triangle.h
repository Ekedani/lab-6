#pragma once

#include "Point.h"
#include "../r-tree/prism.h"
#include <iostream>
#include <cmath>

using namespace std;

class Vector3 {
    double xCoord;
    double yCoord;
    double zCoord;
public:
    Vector3(double x, double y, double z);

    Vector3(const Point &start, const Point &end);

    static double dot(const Vector3 &v1, const Vector3 &v2);

    static Vector3 cross(const Vector3 &v1, const Vector3 &v2);

    static double cosine(const Vector3 &a, const Vector3 &b);

    double Length() const;
};

struct Line {
    Point *point;
    Point *vec; // actually, it isn't a real second point, it's a vector

    Point locationWhenX(double x);

    Point locationWhenY(double y);

    Point locationWhenZ(double z);

    bool doesIntersectParallelepiped(const Prism &prism);
};

struct Plane {
    double A, B, C, D; //Ax+By+C+D=0
    Plane(const Point& a, const Point& b, const Point& c);
};

struct Triangle {
    Point *firstVertex;
    Point *secondVertex;
    Point *thirdVertex;
    bool intersectLine(const Line& line) const;
    Point IntersectionPoint(const Line& line);
};