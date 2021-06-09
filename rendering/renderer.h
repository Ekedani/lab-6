#include "../work-with-bmp/bitmapRender.h"
#include "../data-struct/triangle.h"

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

};

