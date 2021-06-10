#pragma once

#include "Point.h"
#include "../r-tree/prism.h"
#include <iostream>
#include <cmath>

using namespace std;

class Vector3 {
public:
    double xCoord;
    double yCoord;
    double zCoord;

    Vector3(double x, double y, double z);

    Vector3(const Point &start, const Point &end);

    Vector3(const Vector3 &vec);

    Vector3& operator=(const Vector3 &vec);

    Vector3 operator+(const Vector3& vec);

    Vector3 operator*(const double coefficient);

    static double dot(const Vector3 &v1, const Vector3 &v2);

    static Vector3 cross(const Vector3 &v1, const Vector3 &v2);

    static double cosine(const Vector3 &a, const Vector3 &b);

    Vector3 Norm();

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
    Vector3 normal() const;
};

struct Triangle {
    Point *firstVertex;
    Point *secondVertex;
    Point *thirdVertex;
    bool intersectLine(const Line& line) const;
    Point IntersectionPoint(const Line& line);
    Vector3 normal() const;
};