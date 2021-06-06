#pragma once

struct Point{
    double xCoord;
    double yCoord;
    double zCoord;
};

struct Triangle {
    Point* firstVertex;
    Point* secondVertex;
    Point* thirdVertex;
};

class Vector3 {
    double xCoord;
    double yCoord;
    double zCoord;
public:
    Vector3(double x, double y, double z) {
        xCoord = x;
        yCoord = y;
        zCoord = z;
    }
    Vector3(const Point& start, const Point& end) {
        xCoord = end.xCoord - start.xCoord;
        yCoord = end.yCoord - start.yCoord;
        zCoord = end.zCoord - start.zCoord;
    }
    static double dot(const Vector3& v1, const Vector3& v2) {
        return (v1.xCoord*v2.xCoord) + (v1.yCoord*v2.yCoord) + (v1.zCoord*v2.zCoord);
    }
    static Vector3 cross(const Vector3& v1, const Vector3& v2) {
        double x = v1.yCoord*v2.zCoord - v1.zCoord*v2.yCoord;
        double y = v1.zCoord*v2.xCoord - v1.xCoord*v2.zCoord;
        double z = v1.xCoord*v2.yCoord - v1.yCoord*v2.xCoord;
        return Vector3(x,y,z);
    }
};