#include <iostream>
#include "obj-reader/objFileReader.h"
#include "work-with-bmp/bitmapRender.h"
#include "r-tree/r_tree.h"
#include "rendering/renderer.h"

using namespace std;

int main() {
    //Settings of .bmp
    const int SIZE = 1000;

    //Settings of camera
    Point CameraPos{1, 1, 0};
    Point CameraDir{0, 0, 0};
    const double FOV = 60;
    Camera renderCamera{CameraPos, CameraDir, FOV};

    //Settings of light
    Point LightPoint{1, 1, 1};
    LightSource newLightSource(&LightPoint, 251, 153, 52);

    Renderer newRenderer(1000, renderCamera, newLightSource);
    newRenderer.renderOBJ("G:\\my-repos\\lab-6\\cow.obj");

}