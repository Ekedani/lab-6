#include "../data-struct/triangle.h"
#include <algorithm>

class Prism {
private:
    Point* firstPoint;
    Point* secondPoint;
public:

    Prism() {
        firstPoint = nullptr;
        secondPoint = nullptr;
    }

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

    Prism Intersection(const Prism& prism) {
        double firstX = max(this->firstPoint->xCoord, prism.firstPoint->xCoord);
        double firstY = max(this->firstPoint->yCoord, prism.firstPoint->yCoord);
        double firstZ = max(this->firstPoint->zCoord, prism.firstPoint->zCoord);
        auto* intersectionFirst = new Point{firstX, firstY, firstZ};

        double secondX = min(this->secondPoint->xCoord, prism.secondPoint->xCoord);
        double secondY = min(this->secondPoint->yCoord, prism.secondPoint->yCoord);
        double secondZ = min(this->secondPoint->zCoord, prism.secondPoint->zCoord);
        auto* intersectionSecond = new Point{secondX, secondY, secondZ};
        Prism IntersectionPrism(intersectionFirst, intersectionSecond);
        return IntersectionPrism;
    }

    double overlapVolume(const Prism& prism) {
        return this->Intersection(prism).volume();
    }
};
