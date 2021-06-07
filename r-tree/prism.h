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
        if (firstPoint == nullptr || secondPoint == nullptr) {
            cout << "nullptr is caught" << endl;
            return 0;
        }
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

    Prism extend(const Point& point){
        if (this->firstPoint == nullptr) {
            cout << "firstPoint nullptr is caught" << endl;
            return Prism();
        }

        if (this->secondPoint == nullptr) {
            cout << "secondPoint nullptr is caught" << endl;
            return Prism();
        }

        Prism extended;
        double firstX = min(this->firstPoint->xCoord, point.xCoord);
        double firstY = min(this->firstPoint->yCoord, point.yCoord);
        double firstZ = min(this->firstPoint->zCoord, point.zCoord);
        auto* extendedFirst = new Point;
        *extendedFirst = Point{firstX, firstY, firstZ};

        double secondX = max(this->secondPoint->xCoord, point.xCoord);
        double secondY = max(this->secondPoint->yCoord, point.yCoord);
        double secondZ = max(this->secondPoint->zCoord, point.zCoord);
        auto* extendedSecond = new Point;
        *extendedSecond = Point{secondX, secondY, secondZ};

        extended.firstPoint = extendedFirst;
        extended.secondPoint = extendedSecond;

        return extended;
    }
};
