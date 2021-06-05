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
            if(i > 500){
                test[i][j].redComponent = 55;
                test[i][j].greenComponent = 155;
                test[i][j].blueComponent = 45;
            }
            else{
                test[i][j].redComponent = 20;
                test[i][j].greenComponent = 50;
                test[i][j].blueComponent = 10;
            }
        }
    }
    test.writeToFile("lol.bmp");

}
