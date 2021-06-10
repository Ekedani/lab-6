#include <iostream>
#include "obj-reader/objFileReader.h"
#include "work-with-bmp/bitmapRender.h"
#include "r-tree/r_tree.h"
#include "rendering/renderer.h"

using namespace std;

int main() {
    //Пока что работает только с кратными 4 размерами, потом пофиксим
    const int size = 999;
    vector<Triangle *> testVec;
    testVec = objFileReader::readTriangles(/*Insert path to file*/"G:\\my-repos\\lab-6\\cow.obj");

    rTree testTree;

    for (auto &i : testVec) {
        testTree.insertTriangle(i);
    }

    bitmapRender test(size, size);

    Point CameraPos{0, 0, -1.5};
    Point CameraDir{0, 0, 1};

    Point PL{1, 1, 1};
    //LightSource PL(&tmpP);
    Point PlaneOrigin{CameraPos.xCoord + CameraDir.xCoord,
                      CameraPos.yCoord + CameraDir.yCoord,
                      CameraPos.zCoord + CameraDir.zCoord};
    double fov = 60;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {

            test[i][j].redComponent = 255;
            test[i][j].greenComponent = 255;
            test[i][j].blueComponent = 255;

            double xCoord = (i - size / 2) / (double) size;
            double yCoord = -(j - size / 2) / (double) size;

            double distanceToPlaneFromCamera = CameraPos.distanceTo(PlaneOrigin);
            double fovInRad = (fov / 180) * 3.14159265;
            double realPlaneHeight = distanceToPlaneFromCamera * tan(fovInRad);
            Point positionOnPlane{
                    PlaneOrigin.xCoord + xCoord * realPlaneHeight / 2,
                    PlaneOrigin.yCoord + yCoord * realPlaneHeight / 2,
                    PlaneOrigin.zCoord + 0
            };

            Point vectorPositionOnPlane{positionOnPlane.xCoord-CameraPos.xCoord,
                                        positionOnPlane.yCoord-CameraPos.yCoord,
                                        positionOnPlane.zCoord-CameraPos.zCoord};

            Line ray;

            ray.point = &CameraPos;
            ray.vec = &vectorPositionOnPlane;


            vector <Triangle*> searchResults = testTree.findObjectsUsingRay(ray);
            if (!searchResults.empty()) {
                Point tmpPoint = searchResults[0]->IntersectionPoint(ray);
                Vector3 tmpVector1{tmpPoint.xCoord - PL.xCoord, tmpPoint.xCoord - PL.yCoord, tmpPoint.zCoord - PL.zCoord};
                Vector3 tmpVector2{ray.vec->xCoord, ray.vec->yCoord, ray.vec->zCoord};
                Point tmpPoint1{tmpPoint.xCoord - PL.xCoord, tmpPoint.xCoord - PL.yCoord, tmpPoint.zCoord - PL.zCoord};
                //Луч освещения
                Line lightLine;
                lightLine.vec = &tmpPoint1;
                lightLine.point = &PL;
                vector<Triangle*> lightSearchVec = testTree.findObjectsUsingRay(lightLine);
                if(lightSearchVec[0] == searchResults[0]){
                    double coef = fabs(Vector3::cosine(tmpVector1, tmpVector2));
                    test[i][j].redComponent = 255 * coef;
                    test[i][j].greenComponent = 0 * coef;
                    test[i][j].blueComponent = 255 * coef;
                }
                else{
                    test[i][j].redComponent = 0;
                    test[i][j].greenComponent = 0 ;
                    test[i][j].blueComponent = 0;
                }
            }
        }
    }
    test.writeToFile("lol.bmp");
}