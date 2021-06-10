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

void Renderer::renderOBJ(const string &wayToOBJ) {
    vector<Triangle *> triangleVec;
    triangleVec = objFileReader::readTriangles(wayToOBJ);
    rTree triangleTree;
    for (auto &triangle : triangleVec) {
        triangleTree.insertTriangle(triangle);
    }
    bitmapRender bitmapRender(imgSize, imgSize);

    Vector3 dir(renderCamera.pos, renderCamera.dir);
    dir = dir.Norm();

    Vector3 up (0,0,1);
    Vector3 right = Vector3::cross(dir, up);
    right = right.Norm();
    up = Vector3::cross(right,dir);
    up = up.Norm();

    Point PlaneOrigin{renderCamera.pos.xCoord + dir.xCoord,
                      renderCamera.pos.yCoord + dir.yCoord,
                      renderCamera.pos.zCoord + dir.zCoord};
    double distanceToPlaneFromCamera = renderCamera.pos.distanceTo(PlaneOrigin);
    double fovInRad = (renderCamera.fov / 180) * 3.14159265;
    double realPlaneHeight = distanceToPlaneFromCamera * tan(fovInRad);

    up = up*(realPlaneHeight/2);
    right = right*(realPlaneHeight/2);

    for (int i = 0; i < imgSize; ++i) {
        for (int j = 0; j < imgSize; ++j) {

            bitmapRender[i][j].redComponent = BACK_COLOR;
            bitmapRender[i][j].greenComponent = BACK_COLOR;
            bitmapRender[i][j].blueComponent = BACK_COLOR;

            double iNorm = (i - imgSize / 2) / (double) imgSize;
            double jNorm = -(j - imgSize / 2) / (double) imgSize;

            Vector3 vecPosOnPlane = dir + (up*iNorm) + (right*jNorm);

            Point vectorPositionOnPlane{vecPosOnPlane.xCoord,
                                        vecPosOnPlane.yCoord,
                                        vecPosOnPlane.zCoord};

            Line cameraRay;

            cameraRay.point = &renderCamera.pos;
            cameraRay.vec = &vectorPositionOnPlane;

            vector <Triangle*> searchResults = triangleTree.findObjectsUsingRay(cameraRay);
            if (!searchResults.empty()) {
                Point IntersectionPoint = searchResults[0]->IntersectionPoint(cameraRay);

                Point vecIntersectionPoint{IntersectionPoint.xCoord - lamp.sourcePoint->xCoord,
                                           IntersectionPoint.yCoord - lamp.sourcePoint->yCoord,
                                           IntersectionPoint.zCoord - lamp.sourcePoint->zCoord};

                Vector3 tmpVector1{IntersectionPoint.xCoord - lamp.sourcePoint->xCoord,
                                   IntersectionPoint.xCoord - lamp.sourcePoint->yCoord,
                                   IntersectionPoint.zCoord - lamp.sourcePoint->zCoord};

                Vector3 tmpVector2{cameraRay.vec->xCoord, cameraRay.vec->yCoord, cameraRay.vec->zCoord};

                //Луч освещения
                Line lightRay;
                lightRay.point = lamp.sourcePoint;
                lightRay.vec = &vecIntersectionPoint;

                vector<Triangle*> lightSearchVec = triangleTree.findObjectsUsingRay(lightRay);

                if(lightSearchVec[0] == searchResults[0]){
                    Vector3 normVec = searchResults[0]->normal();
                    double coef = fabs(Vector3::cosine(normVec, tmpVector2));
                    bitmapRender[i][j].redComponent = lamp.redComponent * coef;
                    bitmapRender[i][j].greenComponent = lamp.greenComponent * coef;
                    bitmapRender[i][j].blueComponent = lamp.blueComponent * coef;
                }
                else{
                    bitmapRender[i][j].redComponent = 0;
                    bitmapRender[i][j].greenComponent = 0 ;
                    bitmapRender[i][j].blueComponent = 0;
                }

            }
        }
    }
    bitmapRender.writeToFile("result.bmp");
}

Renderer::Renderer(int imgSize, Camera renderCamera, LightSource lamp) {
    this->imgSize = imgSize;
    this->renderCamera = renderCamera;
    this->lamp = lamp;
}
