#include "objFileReader.h"

std::vector<Triangle *> objFileReader::readTriangles(const std::string &filePath) {

    std::ifstream fileStream;
    fileStream.open(filePath);
    std::vector<Triangle *> result;

    //Проверка на то, открыт ли файл
    if (!fileStream.is_open()) {
        return result;
    }

    //Считывание вершин
    std::vector<Point *> vertices = readVertices(fileStream);
    std::string triangleLine;

    //Скип vn раздела
    do {
        getline(fileStream, triangleLine);
    } while (triangleLine.substr(0, 1) != "f" && !fileStream.eof());

    //Считывание f раздела
    while (triangleLine.substr(0, 1) == "f") {
        Triangle *newTriangle = parseFString(triangleLine, vertices);
        result.push_back(newTriangle);
        if (fileStream.eof()) {
            break;
        }
        getline(fileStream, triangleLine);
    }

    fileStream.close();
    return result;
}

std::vector<Point *> objFileReader::readVertices(std::ifstream &filePtr) {
    std::vector<Point *> result;
    std::string curLine;

    //Скипаем начальные строки
    do {
        getline(filePtr, curLine);
    } while (curLine.substr(0, 1) != "v" && !filePtr.eof());

    //Читаем пока есть вершины
    while (curLine.substr(0, 2) != "vn" && !filePtr.eof()) {
        auto *newPoint = new Point;
        curLine.erase(0, 2);

        newPoint->xCoord = std::stod(curLine.substr(0, curLine.find(' ')));
        curLine.erase(0, curLine.find(' ') + 1);

        newPoint->yCoord = std::stod(curLine.substr(0, curLine.find(' ')));
        curLine.erase(0, curLine.find(' ') + 1);

        newPoint->zCoord = std::stod(curLine);

        result.push_back(newPoint);
        getline(filePtr, curLine);
    }
    return result;
}

Triangle *objFileReader::parseFString(std::string stringToParse, std::vector<Point *> pointsVector) {
    auto newTriangle = new Triangle;
    stringToParse.erase(0, 2);
    int pointNum = std::stoi(stringToParse.substr(0, stringToParse.find('/'))) - 1;
    newTriangle->firstVertex = pointsVector[pointNum];
    stringToParse.erase(0, stringToParse.find(' ') + 1);

    pointNum = std::stoi(stringToParse.substr(0, stringToParse.find('/'))) - 1;
    newTriangle->secondVertex = pointsVector[pointNum];
    stringToParse.erase(0, stringToParse.find(' ') + 1);

    pointNum = std::stoi(stringToParse.substr(0, stringToParse.find('/'))) - 1;
    newTriangle->thirdVertex = pointsVector[pointNum];
    return newTriangle;
}
