#include "../data-struct/triangle.h"

class Prism {
private:
    Point* firstPoint;
    Point* secondPoint;
public:

    Prism(Point* p1, Point* p2){
        firstPoint = p1;
        secondPoint = p2;
    }

    double volume() const{
        double a = secondPoint->xCoord - firstPoint->xCoord;
        double b = secondPoint->yCoord - firstPoint->yCoord;
        double c = secondPoint->zCoord - firstPoint->zCoord;
        return a*b*c;
    }
};
