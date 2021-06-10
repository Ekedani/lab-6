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

double Vector3::cosine(const Vector3 &a, const Vector3 &b) {
    return Vector3::dot(a,b)/(a.Length() * b.Length());
}

Plane::Plane(const Point& a, const Point& b, const Point& c){
    A = b.yCoord * c.zCoord - a.yCoord * c.zCoord - b.yCoord * a.zCoord
        - c.yCoord * b.zCoord + c.yCoord * a.zCoord + a.yCoord * b.zCoord;
    B = b.zCoord * c.xCoord - a.zCoord * c.xCoord
        - b.zCoord * a.xCoord - c.zCoord * b.xCoord + c.zCoord * a.xCoord + a.zCoord * b.xCoord;
    C = b.xCoord * c.yCoord - a.xCoord * c.yCoord
        - b.xCoord * a.yCoord - c.xCoord * b.yCoord + c.xCoord * a.yCoord + a.xCoord * b.yCoord;
    D = -a.xCoord * A - a.yCoord * B - a.zCoord * C;
}

Vector3 Plane::normal() const {
    return Vector3(A, B, C);
}

Point Line::locationWhenX(double x) {
    Point realP2
            {point->xCoord + vec->xCoord,
             point->yCoord + vec->yCoord,
             point->zCoord + vec->zCoord
            };
    double deltaX = realP2.xCoord - point->xCoord;
    double deltaY = realP2.yCoord - point->yCoord;
    double deltaZ = realP2.zCoord - point->zCoord;

    double y_component = (x - point->xCoord) * deltaY / deltaX + point->yCoord;
    double z_component = (x - point->xCoord) * deltaZ / deltaX + point->zCoord;
    Point location{x, y_component, z_component};
    return location;
}

Point Line::locationWhenY(double y) {
    Point realP2
            {point->xCoord + vec->xCoord,
             point->yCoord + vec->yCoord,
             point->zCoord + vec->zCoord
            };

    double deltaX = realP2.xCoord - point->xCoord;
    double deltaY = realP2.yCoord - point->yCoord;
    double deltaZ = realP2.zCoord - point->zCoord;

    double x_component = (y - point->yCoord) * deltaX / deltaY + point->xCoord;
    double z_component = (y - point->yCoord) * deltaZ / deltaY + point->zCoord;
    Point location{x_component, y, z_component};
    return location;
}

Point Line::locationWhenZ(double z) {
    Point realP2
            {point->xCoord + vec->xCoord,
             point->yCoord + vec->yCoord,
             point->zCoord + vec->zCoord
            };

    double deltaX = realP2.xCoord - point->xCoord;
    double deltaY = realP2.yCoord - point->yCoord;
    double deltaZ = realP2.zCoord - point->zCoord;

    double x_component = (z - point->zCoord) * deltaX / deltaZ + point->xCoord;
    double y_component = (z - point->zCoord) * deltaY / deltaZ + point->yCoord;
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

bool Triangle::intersectLine(const Line& line) const {
    Vector3 dir(line.vec->xCoord, line.vec->yCoord, line.vec->zCoord);

    Vector3 e1(*firstVertex, *secondVertex);
    Vector3 e2(*firstVertex, *thirdVertex);

    Vector3 pvec = Vector3::cross(dir, e2);
    double det = Vector3::dot(e1, pvec);

    if (det < 1e-8 && det > -1e-8) {
        return 0;
    }

    double inv_det = 1 / det;
    Vector3 tvec(*firstVertex, *line.point);
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

Point Triangle::IntersectionPoint(const Line &line) {
    Plane plane(*firstVertex, *secondVertex, *thirdVertex);
    double k = plane.A * line.vec->xCoord + plane.B * line.vec->yCoord + plane.C * line.vec->zCoord;
    double t = -(plane.A * line.point->xCoord + plane.B * line.point->yCoord + plane.C * line.point->zCoord + plane.D) / k;
    Point Intersection = Point{line.point->xCoord + line.vec->xCoord * t, line.point->yCoord + line.vec->yCoord * t, line.point->zCoord + line.vec->zCoord * t};
    return Intersection;
}

Vector3 Triangle::normal() const {
    Plane plane(*firstVertex, *secondVertex, *thirdVertex);
    return plane.normal();
}
