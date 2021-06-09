#include "bitmapRender.h"

void bitmapRender::writeToFile(const std::string &filePath) {
    writeHeader(filePath);
    writePixelsToFile(filePath);
}

Pixel *&bitmapRender::operator[](int index) {
    return pixels[index];
}

bitmapRender::bitmapRender(int32_t width, int32_t depth) {
    this->width = width;
    this->depth = depth;
    pixels = new Pixel *[depth];
    for (int i = 0; i < depth; ++i) {
        pixels[i] = new Pixel[width];
    }

    int delta = 4 - ((width * 3) % 4);
    if (((width * 3) % 4) == 0) {
        delta = 0;
    }
    this->filesize = 54 + (depth * width) * 3 + delta * depth;

    //Мусор, без которого файл не будет записываться
    id[0] = 'B';
    id[1] = 'M';
    reserved[0] = 0;
    reserved[1] = 0;
    headersize = 54L;
    infoSize = 40L;
    biPlanes = 1;
    bits = 24;
    biCompression = 0L;
    biSizeImage = 0L;
    biXPelsPerMeter = 0L;
    biYPelsPerMeter = 0L;
    biClrUsed = 0L;
    biClrImportant = 0L;
}

void bitmapRender::writePixelsToFile(const std::string &address) const {
    int delta = 4 - ((width * 3) % 4);
    if (((width * 3) % 4) == 0) {
        delta = 0;
    }

    std::ofstream file(address, std::ios::out | std::ios::binary | std::ios::app);
    for (int i = 0; i < depth; i++) {
        this->writeLine(file, i);
        for (int j = 0; j < delta; j++) {
            uint8_t zero = 0;
            file.write((char *) &zero, sizeof(uint8_t));
        }
    }
    file.close();
}

void bitmapRender::writeLine(std::ofstream &file, int proceededLines) const {
    for (int counter = 0; counter < width; ++counter) {
        //Запись цвета пикселя
        uint8_t red = pixels[proceededLines][counter].redComponent;
        file.write((char *) &red, sizeof(uint8_t));
        uint8_t green = pixels[proceededLines][counter].greenComponent;
        file.write((char *) &green, sizeof(uint8_t));
        uint8_t blue = pixels[proceededLines][counter].blueComponent;
        file.write((char *) &blue, sizeof(uint8_t));
    }
}

int32_t bitmapRender::getWidth() const {
    return width;
}

int32_t bitmapRender::getDepth() const {
    return depth;
}

void bitmapRender::writeHeader(const std::string &filePath) {
    std::ofstream file(filePath, std::ios::out | std::ios::binary);
    file.write((char *) &id, sizeof(id));
    file.write((char *) &filesize, sizeof(filesize));
    file.write((char *) &reserved, sizeof(reserved));
    file.write((char *) &headersize, sizeof(headersize));
    file.write((char *) &infoSize, sizeof(infoSize));
    file.write((char *) &width, sizeof(width));
    file.write((char *) &depth, sizeof(depth));
    file.write((char *) &biPlanes, sizeof(biPlanes));
    file.write((char *) &bits, sizeof(bits));
    file.write((char *) &biCompression, sizeof(biCompression));
    file.write((char *) &biSizeImage, sizeof(biSizeImage));
    file.write((char *) &biXPelsPerMeter, sizeof(biXPelsPerMeter));
    file.write((char *) &biYPelsPerMeter, sizeof(biYPelsPerMeter));
    file.write((char *) &biClrUsed, sizeof(biClrUsed));
    file.write((char *) &biClrImportant, sizeof(biClrImportant));
    file.close();
}
