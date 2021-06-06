#include <iostream>
#include "obj-reader/objFileReader.h"
#include "work-with-bmp/bitmapRender.h"
using namespace std;

int main() {
    //Пока что работает только с кратными 4 размерами, потом пофиксим
    const int size = 16;
    vector<Triangle*> testVec;
    //введи свой адрес
    testVec = objFileReader::readTriangles("C:\\Users\\koziu\\Desktop\\Labs\\lab-6\\cube.obj");

    cout << "testVec size: " << testVec.size() << endl;
    cout << "testVec[0]: " << endl;
    cout << "vert1: " << testVec[0]->firstVertex->xCoord << " " << testVec[0]->firstVertex->yCoord
         << " " << testVec[0]->firstVertex->zCoord << endl;
    cout << "vert2: " << testVec[0]->secondVertex->xCoord << " " << testVec[0]->secondVertex->yCoord
         << " " << testVec[0]->secondVertex->zCoord << endl;
    cout << "vert3: " << testVec[0]->secondVertex->xCoord << " " << testVec[0]->secondVertex->yCoord
         << " " << testVec[0]->secondVertex->zCoord << endl;

    bitmapRender test(size, size);
    Point Camera{0,0,-2};

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {

            test[i][j].redComponent =  255;
            test[i][j].greenComponent = 255;
            test[i][j].blueComponent = 255;

            double xCoord = (i - size/2)/(double)size;
            double yCoord = (j - size/2)/(double)size;
            double zCoord = -2;
            Point current{xCoord, yCoord, zCoord};

            /* DEBUG
            cout << "xCurrent: " << current.xCoord << endl;
            cout << "yCurrent: " << current.yCoord << endl;
            cout << "zCurrent: " << current.zCoord << endl;
            */
            Line ray;
            ray.p1 = &current;
            ray.p2 = &Camera;
            for (int k = 0; k < testVec.size(); ++k) {
                if (ray.triangle_intersection(*testVec[k]) != 0) {
                    cout << "V" << endl;
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
