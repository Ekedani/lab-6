#include <iostream>
#include "obj-reader/objFileReader.h"
#include "work-with-bmp/bitmapRender.h"
#include "r-tree/r_tree.h"

using namespace std;

int main() {
    //Пока что работает только с кратными 4 размерами, потом пофиксим
    const int size = 256;
    vector<Triangle*> testVec;
    testVec = objFileReader::readTriangles("G:\\my-repos\\lab-6\\cow.obj");
    /*
    for (int i = 0; i < testVec.size(); ++i) {
        TriangleLeaf t (testVec[i]);
        t.print();
        t.printMBR();
    }
     */


    ////ТРЕУГОЛЬНИК
    Point p1{-0.428017, 0.056587, -0.093474};
    Point p2{-0.440513, 0.048295, -0.065657};
    Point p3{-0.43362, 0.069116 , -0.048645};
    ////ЛУЧ
    Point p4{-0.433013, 0.0676582, 4};
    Point p5{0, 0, -5};
    Triangle *testTriangle = new Triangle{&p1, &p2, &p3};
    Line newline{&p4, &p5};

    rTree testTree;
    TriangleLeaf testLeaf(testTriangle);
    cout << testVec.size() << '\n';

    for (int i = 0; i < testVec.size(); ++i) {
        testTree.insertTriangle(testVec[i]);
    }
    testTree.insertTriangle(testTriangle);
    bitmapRender test(size, size);

    vector <Triangle *> Fine = testTree.findObjectsUsingRay(newline);
    cout << newline.triangle_intersection(*testTriangle) << '\n';
    cout << newline.doesIntersectParallelepiped(testLeaf.MBP) << '\n';
    cout << Fine.size() << '\n';

    testTree.debugTreeParse(testTriangle, &newline);

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

/*
            for (int k = 0; k < testVec.size(); ++k) {
                if (ray.triangle_intersection(*testVec[k]) != 0) {
                    //cout << "V" << endl;
                    test[i][j].redComponent =  100;
                    test[i][j].greenComponent = 100;
                    test[i][j].blueComponent = 100;
                    break;
                }
            }
             */

            if (!testTree.findObjectsUsingRay(ray).empty()) {
                test[i][j].redComponent =  100;
                test[i][j].greenComponent = 100;
                test[i][j].blueComponent = 100;
            }
        }
    }

    test.writeToFile("lol.bmp");

}