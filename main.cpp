#include <iostream>
#include "obj-reader/objFileReader.h"

using namespace std;

int main() {

    vector<Triangle*> testVec;
    testVec = objFileReader::readTriangles("G:\\cow.obj");

}
