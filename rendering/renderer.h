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

    LightSource()= default;

    //Белый цвет
    explicit LightSource(Point *sourcePoint);

    //Любой цвет
    LightSource(Point *sourcePoint, uint16_t R, uint16_t G, uint16_t B);
};

struct Camera{
    Point pos;
    Point dir;
    double fov;
};

//Содержит всю логику рендеринга
class Renderer {
private:
    //Параметры для рендера
    static const uint8_t BACK_COLOR = 50;
    Camera renderCamera{};
    LightSource lamp{};
    int imgSize;
    
public:
    Renderer(int imgSize, Camera renderCamera, LightSource lamp);

    void renderOBJ(const std::string& wayToOBJ);
};

