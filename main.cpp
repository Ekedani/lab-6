#include <iostream>
#include "obj-reader/objFileReader.h"
#include "work-with-bmp/bitmapRender.h"
using namespace std;

int main() {
    //Пока что работает только с кратными 4 размерами, потом пофиксим
    const int size = 256;
    vector<Triangle*> testVec;
    testVec = objFileReader::readTriangles("C:\\Users\\koziu\\Desktop\\Labs\\lab-6\\cow.obj");

/*
    cout << "testVec size: " << testVec.size() << endl;
    cout << "testVec[i]: " << endl;
    for (int i = 0; i < testVec.size(); ++i) {
        cout << "vert1: " << testVec[i]->firstVertex->xCoord << " " << testVec[i]->firstVertex->yCoord
             << " " << testVec[i]->firstVertex->zCoord << endl;
        cout << "vert2: " << testVec[i]->secondVertex->xCoord << " " << testVec[i]->secondVertex->yCoord
             << " " << testVec[i]->secondVertex->zCoord << endl;
        cout << "vert3: " << testVec[i]->thirdVertex->xCoord << " " << testVec[i]->thirdVertex->yCoord
             << " " << testVec[i]->thirdVertex->zCoord << endl;
    }
*/
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

            /* DEBUG
            cout << "xCurrent: " << current.xCoord << endl;
            cout << "yCurrent: " << current.yCoord << endl;
            cout << "zCurrent: " << current.zCoord << endl;
            */
            Line ray;
            ray.p1 = &positionOnPlane;
            ray.p2 = &CameraPos;
            for (int k = 0; k < testVec.size(); ++k) {
                if (ray.triangle_intersection(*testVec[k]) != 0) {
                    //cout << "V" << endl;
                    test[i][j].redComponent =  100;
                    test[i][j].greenComponent = 100;
                    test[i][j].blueComponent = 100;
                    break;
                }
            }
        }
    }


    test.writeToFile("lol.bmp");

}
