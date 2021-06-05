#include "bitmapRender.h"

void bitmapRender::writeToFile(const std::string& filePath) {

}

Pixel *&bitmapRender::operator[](int index) {
    return pixels[index];
}

bitmapRender::bitmapRender(int32_t width, int32_t depth) {
    this->width = width;
    this->depth = depth;
    pixels = new Pixel*[depth];
    for (int i = 0; i < depth; ++i) {
        pixels[i] = new Pixel[width];
    }
}

void bitmapRender::writePixelsToFile(const std::string &address) const {
    int delta = 4 - ((width * 3) % 4);
    std::ofstream file (address, std::ios::out | std::ios::binary | std::ios::app);
    for(int i = 0; i < depth; i++){
        this->writeLine(file, i);
        for(int j = 0; j < delta; j++){
            uint8_t zero = 0;
            file.write((char*)&zero, sizeof(uint8_t));
        }
    }
    file.close();
}

void bitmapRender::writeLine(std::ofstream &file, int proceededLines) const {
    for (int counter = 0; counter < width; ++counter) {
        //Запись цвета пикселя
        uint8_t red = pixels[proceededLines][counter].redComponent;
        file.write((char*)&red, sizeof(uint8_t));
        uint8_t green = pixels[proceededLines][counter].greenComponent;
        file.write((char*)&green, sizeof(uint8_t));
        uint8_t blue = pixels[proceededLines][counter].blueComponent;
        file.write((char*)&blue, sizeof(uint8_t));
    }
}
