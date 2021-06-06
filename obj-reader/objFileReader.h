#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "../data-struct/triangle.h"

class objFileReader {
private:
    //Считывает точки
    static std::vector<Point*> readVertices(std::ifstream& filePtr);

    //Считывает строку с префиксом f
    static Triangle* parseFString(std::string stringToParse, std::vector<Point*> pointsVector);

public:
    //Возвращает информацию о треугольниках, записанных в файле
    static std::vector <Triangle*> readTriangles(const std::string &filePath);
};
