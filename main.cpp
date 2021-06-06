#include <iostream>
#include "obj-reader/objFileReader.h"
#include "work-with-bmp/bitmapRender.h"
using namespace std;

int main() {
    //Пока что работает только с кратными 4 размерами, потом пофиксим
    const int size = 1000;
    vector<Triangle*> testVec;
    testVec = objFileReader::readTriangles("G:\\cow.obj");
    bitmapRender test(size, size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            test[i][j].redComponent =  20;
            test[i][j].greenComponent = i % 255;
            test[i][j].blueComponent = i % 255;
        }
    }
    test.writeToFile("lol.bmp");

}
