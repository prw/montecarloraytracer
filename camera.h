#ifndef CAMERA_H
#define CAMERA_H
#include "vector.h"
#include "point.h"
#include "ray.h"
class Camera {
public:
    Point position;
    Vector up, direction, right;
    double height, width, largest;
    Point **image;

    Camera(Point pos, Vector camup, Vector dir, double h, double w);

    void getRay(int i, int j, Ray &r);
    void setPixel(int i, int j, Point color);
    void writeImage(char *fname);
};

#endif // CAMERA_H
