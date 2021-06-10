#include "renderer.h"

LightSource::LightSource(Point *sourcePoint) {
    this->sourcePoint = sourcePoint;
    redComponent = 255;
    greenComponent = 255;
    blueComponent = 255;
}

LightSource::LightSource(Point *sourcePoint, uint16_t R, uint16_t G, uint16_t B) {
    this->sourcePoint = sourcePoint;
    redComponent = R;
    greenComponent = G;
    blueComponent = B;
}

void Renderer::renderOBJ(int imgSize, const string &wayToOBJ) {
    vector<Triangle *> triangleVec;
    triangleVec = objFileReader::readTriangles(wayToOBJ);
    rTree triangleTree;
    for (auto &triangle : triangleVec) {
        triangleTree.insertTriangle(triangle);
    }
    bitmapRender renderedImage(imgSize, imgSize);

    //Настройка камеры и ее параметров
    Camera renderCamera{};
    renderCamera.position =  Point{0, 0, -1.5};
    renderCamera.fov = 60;
    renderCamera.direction = Point{0, 0, 1};

    //Выбор точки и цвета освещения
    Point lightPoint{1, 1, 1};
    LightSource lamp(&lightPoint, 251, 153, 52);


    Point PlaneOrigin{renderCamera.position.xCoord + renderCamera.direction.xCoord,
                      renderCamera.position.yCoord + renderCamera.direction.yCoord,
                      renderCamera.position.zCoord + renderCamera.direction.zCoord};

    for (int i = 0; i < imgSize; ++i) {
        for (int j = 0; j < imgSize; ++j) {

            renderedImage[i][j].redComponent = BACK_COLOR;
            renderedImage[i][j].greenComponent = BACK_COLOR;
            renderedImage[i][j].blueComponent = BACK_COLOR;

            double xCoord = (i - imgSize / 2) / (double) imgSize;
            double yCoord = -(j - imgSize / 2) / (double) imgSize;

            double distanceToPlaneFromCamera = renderCamera.position.distanceTo(PlaneOrigin);
            double fovInRad = (renderCamera.fov / 180) * 3.14159265;
            double realPlaneHeight = distanceToPlaneFromCamera * tan(fovInRad);
            Point positionOnPlane{
                    PlaneOrigin.xCoord + xCoord * realPlaneHeight / 2,
                    PlaneOrigin.yCoord + yCoord * realPlaneHeight / 2,
                    PlaneOrigin.zCoord + 0
            };

            Point vectorPositionOnPlane{positionOnPlane.xCoord - renderCamera.position.xCoord,
                                        positionOnPlane.yCoord - renderCamera.position.yCoord,
                                        positionOnPlane.zCoord - renderCamera.position.zCoord};

            Line ray;

            ray.point = &renderCamera.position;
            ray.vec = &vectorPositionOnPlane;


            vector<Triangle *> searchResults = triangleTree.findObjectsUsingRay(ray);
            if (!searchResults.empty()) {

                Point IntersectionPoint = searchResults[0]->IntersectionPoint(ray);


                Point vecIntersectionPoint{IntersectionPoint.xCoord - lamp.sourcePoint->xCoord,
                                           IntersectionPoint.yCoord - lamp.sourcePoint->yCoord,
                                           IntersectionPoint.zCoord - lamp.sourcePoint->zCoord};

                Vector3 tmpVector1{IntersectionPoint.xCoord - lamp.sourcePoint->xCoord,
                                   IntersectionPoint.xCoord - lamp.sourcePoint->yCoord,
                                   IntersectionPoint.zCoord - lamp.sourcePoint->zCoord};
                Vector3 tmpVector2{ray.vec->xCoord, ray.vec->yCoord, ray.vec->zCoord};

                //Луч освещения
                Line lightLine;
                lightLine.point = lamp.sourcePoint;
                lightLine.vec = &vecIntersectionPoint;

                vector<Triangle *> lightSearchVec = triangleTree.findObjectsUsingRay(lightLine);

                if (lightSearchVec[0] == searchResults[0]) {
                    Vector3 normVec = searchResults[0]->normal();
                    double coef = fabs(Vector3::cosine(normVec, tmpVector2));
                    renderedImage[i][j].redComponent = lamp.redComponent * coef;
                    renderedImage[i][j].greenComponent = lamp.greenComponent * coef;
                    renderedImage[i][j].blueComponent = lamp.blueComponent * coef;
                } else {
                    renderedImage[i][j].redComponent = 0;
                    renderedImage[i][j].greenComponent = 0;
                    renderedImage[i][j].blueComponent = 0;
                }
            }
        }
    }
    renderedImage.writeToFile(/*Select your path*/"lol.bmp");
}
