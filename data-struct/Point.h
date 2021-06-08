#pragma once
#include <cmath>
#include <iostream>
using namespace std;
struct Point{
    double xCoord;
    double yCoord;
    double zCoord;
    double distanceTo(const Point& other) {
        double deltaX = (this->xCoord - other.xCoord);
        double deltaY = (this->yCoord - other.yCoord);
        double deltaZ = (this->zCoord - other.zCoord);
        return sqrt(deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ);
    }
    void print() {
        cout << xCoord << " " << yCoord << " " << zCoord << endl;
    }
};