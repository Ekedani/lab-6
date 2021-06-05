#pragma once
#include <cstdint>
#include <string>

struct Pixel{
    uint8_t redComponent;
    uint8_t greenComponent;
    uint8_t blueComponent;
};

class bitmapRender {
private:

public:
    void writeToFile(const std::string& filePath);
};