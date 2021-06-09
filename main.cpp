#include <iostream>
#include "obj-reader/objFileReader.h"
#include "work-with-bmp/bitmapRender.h"
#include "r-tree/r_tree.h"

using namespace std;

int main() {
    //Пока что работает только с кратными 4 размерами, потом пофиксим
    const int size = 256;
    vector<Triangle*> testVec;
    testVec = objFileReader::readTriangles(/*Insert path to file*/"");

    rTree testTree;
    cout << testVec.size() << '\n';

    for (auto & i : testVec) {
        testTree.insertTriangle(i);
    }

    bitmapRender test(size, size);

    Point CameraPos{0,0, -5};
    Point CameraDir{0, 0, 1};
    Point PlaneOrigin{CameraPos.xCoord + CameraDir.xCoord,
                      CameraPos.yCoord+CameraDir.yCoord,
                      CameraPos.zCoord+CameraDir.zCoord};
    double fov = 60;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {

            test[i][j].redComponent =  255;
            test[i][j].greenComponent = 255;
            test[i][j].blueComponent = 255;

            double xCoord = (i - size/2)/(double)size;
            double yCoord = -(j - size/2)/(double)size;

            double distanceToPlaneFromCamera = CameraPos.distanceTo(PlaneOrigin);
            double fovInRad = (fov/180)*3.14159265;
            double realPlaneHeight = distanceToPlaneFromCamera * tan(fovInRad);
            Point positionOnPlane{
                    PlaneOrigin.xCoord + xCoord*realPlaneHeight/2,
                    PlaneOrigin.yCoord + yCoord*realPlaneHeight/2,
                    PlaneOrigin.zCoord+0
            };

            Line ray;
            ray.p1 = &positionOnPlane;
            ray.p2 = &CameraPos;


            if (!testTree.findObjectsUsingRay(ray).empty()) {
                test[i][j].redComponent =  0;
                test[i][j].greenComponent = 0;
                test[i][j].blueComponent = 255;
            }
        }
    }

    test.writeToFile("lol.bmp");

}