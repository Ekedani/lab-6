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
