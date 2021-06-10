#include <iostream>
#include "obj-reader/objFileReader.h"
#include "work-with-bmp/bitmapRender.h"
#include "r-tree/r_tree.h"
#include "rendering/renderer.h"

using namespace std;

int main() {
    const int size = 999;
    vector<Triangle *> testVec;
    testVec = objFileReader::readTriangles(/*Insert path to file*/"G:\\my-repos\\lab-6\\cow.obj");

    rTree testTree;

    for (auto &i : testVec) {
        testTree.insertTriangle(i);
    }

    bitmapRender test(size, size);

    Point CameraPos{1, 1, 0};
    Point CameraDir{0, 0, 0};

    Point PL{1, 1, 1};
    //LightSource PL(&tmpP);


    Vector3 dir(CameraPos, CameraDir);
    dir = dir.Norm();

    Vector3 up (0,0,1);
    Vector3 right = Vector3::cross(dir, up);
    right = right.Norm();
    Vector3 actual_up = Vector3::cross(right,dir);
    actual_up = actual_up.Norm();

    Point PlaneOrigin{CameraPos.xCoord + dir.xCoord,
                      CameraPos.yCoord + dir.yCoord,
                      CameraPos.zCoord + dir.zCoord};

    double fov = 60;
    double distanceToPlaneFromCamera = CameraPos.distanceTo(PlaneOrigin);
    double fovInRad = (fov / 180) * 3.14159265;
    double realPlaneHeight = distanceToPlaneFromCamera * tan(fovInRad);

    actual_up = actual_up*(realPlaneHeight/2);
    right = right*(realPlaneHeight/2);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {

            test[i][j].redComponent = 255;
            test[i][j].greenComponent = 255;
            test[i][j].blueComponent = 255;

            double iNorm = (i - size / 2) / (double) size;
            double jNorm = -(j - size / 2) / (double) size;

            Vector3 vecPosOnPlane = dir + (actual_up*iNorm) + (right*jNorm);

            Point vectorPositionOnPlane{vecPosOnPlane.xCoord,
                                        vecPosOnPlane.yCoord,
                                        vecPosOnPlane.zCoord};

            Line ray;

            ray.point = &CameraPos;
            ray.vec = &vectorPositionOnPlane;


            vector <Triangle*> searchResults = testTree.findObjectsUsingRay(ray);
            if (!searchResults.empty()) {

                Point IntersectionPoint = searchResults[0]->IntersectionPoint(ray);


                Point vecIntersectionPoint{IntersectionPoint.xCoord - PL.xCoord,
                                           IntersectionPoint.yCoord - PL.yCoord,
                                           IntersectionPoint.zCoord - PL.zCoord};

                Vector3 tmpVector1{IntersectionPoint.xCoord - PL.xCoord,
                                   IntersectionPoint.xCoord - PL.yCoord,
                                   IntersectionPoint.zCoord - PL.zCoord};
                Vector3 tmpVector2{ray.vec->xCoord, ray.vec->yCoord, ray.vec->zCoord};

                //Луч освещения
                Line lightLine;
                lightLine.point = &PL;
                lightLine.vec = &vecIntersectionPoint;

                vector<Triangle*> lightSearchVec = testTree.findObjectsUsingRay(lightLine);

                if(lightSearchVec[0] == searchResults[0]){
                    Vector3 normVec = searchResults[0]->normal();
                    double coef = fabs(Vector3::cosine(normVec, tmpVector2));
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