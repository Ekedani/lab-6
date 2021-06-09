#include "Point.h"

double Point::distanceTo(const Point &other) const {
    double deltaX = (this->xCoord - other.xCoord);
    double deltaY = (this->yCoord - other.yCoord);
    double deltaZ = (this->zCoord - other.zCoord);
    return sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
}
