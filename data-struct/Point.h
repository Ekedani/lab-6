#pragma once

#include <cmath>
#include <iostream>

using namespace std;

struct Point {
    double xCoord;
    double yCoord;
    double zCoord;

    double distanceTo(const Point &other) const;

    void print() {
        cout << xCoord << " " << yCoord << " " << zCoord << endl;
    }
};