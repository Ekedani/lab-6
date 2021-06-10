#include "../work-with-bmp/bitmapRender.h"
#include "../data-struct/triangle.h"
#include "../obj-reader/objFileReader.h"
#include "../r-tree/r_tree.h"

#include <fstream>
#include <vector>

struct LightSource {
    uint8_t redComponent;
    uint8_t greenComponent;
    uint8_t blueComponent;

    Point *sourcePoint;

    //Белый цвет
    explicit LightSource(Point *sourcePoint);

    //Любой цвет
    LightSource(Point *sourcePoint, uint16_t R, uint16_t G, uint16_t B);
};

//В теории будет содержать всю логику рендеринга
class Renderer {
private:

public:
    static void renderOBJ(int imgSize, const std::string& wayToOBJ){
        vector<Triangle *> triangleVec;
        triangleVec = objFileReader::readTriangles(wayToOBJ);
        rTree triangleTree;
        for (auto &triangle : triangleVec) {
            triangleTree.insertTriangle(triangle);
        }
        bitmapRender renderedImage(imgSize, imgSize);
    }
};

