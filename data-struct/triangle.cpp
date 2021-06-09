#include "triangle.h"

Vector3::Vector3(double x, double y, double z) {
    xCoord = x;
    yCoord = y;
    zCoord = z;
}

Vector3::Vector3(const Point &start, const Point &end) {
    xCoord = end.xCoord - start.xCoord;
    yCoord = end.yCoord - start.yCoord;
    zCoord = end.zCoord - start.zCoord;
}

double Vector3::dot(const Vector3 &v1, const Vector3 &v2) {
    return (v1.xCoord * v2.xCoord) + (v1.yCoord * v2.yCoord) + (v1.zCoord * v2.zCoord);
}

Vector3 Vector3::cross(const Vector3 &v1, const Vector3 &v2) {
    double x = v1.yCoord * v2.zCoord - v1.zCoord * v2.yCoord;
    double y = v1.zCoord * v2.xCoord - v1.xCoord * v2.zCoord;
    double z = v1.xCoord * v2.yCoord - v1.yCoord * v2.xCoord;
    return Vector3(x, y, z);
}

double Vector3::Length() const {
    return sqrt(xCoord * xCoord + yCoord * yCoord + zCoord * zCoord);
}

double Line::triangle_intersection(const Triangle &triangle) const {
    Vector3 dir(p2->xCoord, p2->yCoord, p2->zCoord);

    Vector3 e1(*triangle.firstVertex, *triangle.secondVertex);
    Vector3 e2(*triangle.firstVertex, *triangle.thirdVertex);

    Vector3 pvec = Vector3::cross(dir, e2);
    double det = Vector3::dot(e1, pvec);

    if (det < 1e-8 && det > -1e-8) {
        return 0;
    }

    double inv_det = 1 / det;
    Vector3 tvec(*triangle.firstVertex, *p1);
    double u = Vector3::dot(tvec, pvec) * inv_det;
    if (u < 0 || u > 1) {
        return 0;
    }
    Vector3 qvec = Vector3::cross(tvec, e1);
    double v = Vector3::dot(dir, qvec) * inv_det;
    if (v < 0 || u + v > 1) {
        return 0;
    }
    return Vector3::dot(e2, qvec) * inv_det;
}

Point Line::intersectionWithTriangle(const Triangle &triangle) {
    Vector3 dir(p2->xCoord, p2->yCoord, p2->zCoord);
    Vector3 e1(*triangle.firstVertex, *triangle.secondVertex);
    Vector3 e2(*triangle.firstVertex, *triangle.thirdVertex);
    Vector3 pvec = Vector3::cross(dir, e2);
    double det = Vector3::dot(e1, pvec);
    double inv_det = 1 / det;
    Vector3 tvec(*triangle.firstVertex, *p1);
    double u = Vector3::dot(tvec, pvec) * inv_det;
    double x = u;

    return this->locationWhenX(x);
}

Point Line::locationWhenX(double x) {
    Point realP2
            {p1->xCoord + p2->xCoord,
             p1->yCoord + p2->yCoord,
             p1->zCoord + p2->zCoord
            };
    double deltaX = realP2.xCoord - p1->xCoord;
    double deltaY = realP2.yCoord - p1->yCoord;
    double deltaZ = realP2.zCoord - p1->zCoord;

    double y_component = (x - p1->xCoord) * deltaY / deltaX + p1->yCoord;
    double z_component = (x - p1->xCoord) * deltaZ / deltaX + p1->zCoord;
    Point location{x, y_component, z_component};
    return location;
}

Point Line::locationWhenY(double y) {
    Point realP2
            {p1->xCoord + p2->xCoord,
             p1->yCoord + p2->yCoord,
             p1->zCoord + p2->zCoord
            };

    double deltaX = realP2.xCoord - p1->xCoord;
    double deltaY = realP2.yCoord - p1->yCoord;
    double deltaZ = realP2.zCoord - p1->zCoord;

    double x_component = (y - p1->yCoord) * deltaX / deltaY + p1->xCoord;
    double z_component = (y - p1->yCoord) * deltaZ / deltaY + p1->zCoord;
    Point location{x_component, y, z_component};
    return location;
}

Point Line::locationWhenZ(double z) {
    Point realP2
            {p1->xCoord + p2->xCoord,
             p1->yCoord + p2->yCoord,
             p1->zCoord + p2->zCoord
            };

    double deltaX = realP2.xCoord - p1->xCoord;
    double deltaY = realP2.yCoord - p1->yCoord;
    double deltaZ = realP2.zCoord - p1->zCoord;

    double x_component = (z - p1->zCoord) * deltaX / deltaZ + p1->xCoord;
    double y_component = (z - p1->zCoord) * deltaY / deltaZ + p1->yCoord;
    Point location{x_component, y_component, z};
    return location;
}

bool Line::doesIntersectParallelepiped(const Prism &prism) {

    Point firstPoint = *prism.getFirstPoint();
    Point secondPoint = *prism.getSecondPoint();

    double x_1 = firstPoint.xCoord;
    double y_1 = firstPoint.yCoord;
    double z_1 = firstPoint.zCoord;

    double x_2 = secondPoint.xCoord;
    double y_2 = secondPoint.yCoord;
    double z_2 = secondPoint.zCoord;

    if (prism.isInside(this->locationWhenX(x_1))) {
        return true;
    }
    if (prism.isInside(this->locationWhenX(x_2))) {
        return true;
    }

    if (prism.isInside(this->locationWhenY(y_1))) {
        return true;
    }
    if (prism.isInside(this->locationWhenY(y_2))) {
        return true;
    }

    if (prism.isInside(this->locationWhenZ(z_1))) {
        return true;
    }
    return prism.isInside(this->locationWhenZ(z_2));

}
