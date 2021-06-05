#pragma once
#include <cstdint>
#include <string>
#include <fstream>

struct Pixel{
    uint8_t redComponent;
    uint8_t greenComponent;
    uint8_t blueComponent;
};

class bitmapRender {
private:
    //Размеры файла
    int32_t filesize;
    int32_t width;
    int32_t depth;

    //Информация о пикселях
    Pixel** pixels;

    //Запись массива пикселей в файл
    void writePixelsToFile(const std::string& address) const;

    //Запись строки массива в файл
    void writeLine(std::ofstream &file, int proceededLines) const;

    void writeHeader(const std::string& filePath){
        
    }

public:
    //Запись в .bmp файл
    void writeToFile(const std::string& filePath);

    //Оператор индексации, чтобы тебе жилось проще
    Pixel*& operator[](int index);

    //Конструктор
    bitmapRender(int32_t width, int32_t depth);

    //Запись в файл
    void writeImage(const std::string& filePath){
        writeHeader(filePath);
        writePixelsToFile(filePath);
    }
};