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

    //Дефолтная информация, которая нужна только для записи
    int8_t id[2];
    int16_t reserved[2];
    int32_t headersize;
    int32_t infoSize;
    int16_t biPlanes;
    int16_t bits;
    int32_t biCompression;
    int32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    int32_t biClrUsed;
    int32_t biClrImportant;


    //Информация о пикселях
    Pixel** pixels;

    //Запись массива пикселей в файл
    void writePixelsToFile(const std::string& address) const;

    //Запись строки массива в файл
    void writeLine(std::ofstream &file, int proceededLines) const;

    //Запись хедера в файл
    void writeHeader(const std::string& filePath);

public:
    //Запись в .bmp файл
    void writeToFile(const std::string& filePath);

    //Оператор индексации, чтобы тебе жилось проще
    Pixel*& operator[](int index);

    //Конструктор
    bitmapRender(int32_t width, int32_t depth);

    //Геттеры глубины и ширины
    int32_t getWidth() const;
    int32_t getDepth() const;


};