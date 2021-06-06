#include "renderer.h"

LightSource::LightSource(Point *sourcePoint) {
    this->sourcePoint = sourcePoint;
    redComponent = 255;
    greenComponent = 255;
    blueComponent = 255;
}

LightSource::LightSource(Point *sourcePoint, uint16_t R, uint16_t G, uint16_t B) {
    this->sourcePoint = sourcePoint;
    redComponent = R;
    greenComponent = G;
    blueComponent = B;
}
