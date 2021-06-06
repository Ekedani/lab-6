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

struct Line {
    Point* p1;
    Point* p2;
    float triangle_intersection(const Triangle& triangle) {
        Vector3 dir(p2->xCoord, p2->yCoord, p2->zCoord);

        Vector3 e1(*triangle.firstVertex, *triangle.secondVertex);
        Vector3 e2(*triangle.firstVertex, *triangle.thirdVertex);

        Vector3 pvec = Vector3::cross(dir, e2);
        float det = Vector3::dot(e1, pvec);

        if (det < 1e-8 && det > -1e-8) {
            return 0;
        }

        float inv_det = 1 / det;
        Vector3 tvec(*triangle.firstVertex, *p1);
        float u = Vector3::dot(tvec, pvec) * inv_det;
        if (u < 0 || u > 1) {
            return 0;
        }
        Vector3 qvec = Vector3::cross(tvec, e1);
        float v = Vector3::dot(dir, qvec) * inv_det;
        if (v < 0 || u + v > 1) {
            return 0;
        }
        return Vector3::dot(e2, qvec) * inv_det;
    }
};