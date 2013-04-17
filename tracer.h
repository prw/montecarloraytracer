#ifndef TRACER_H
#define TRACER_H
#include "camera.h"
#include "scene.h"

class Tracer{
public:
    Camera *c;
    Scene *s;
    Tracer(Camera *cc, Scene *s);
    void trace(char *img, int recursions, int aa);
    void _trace(Ray &r, Point &color, int recurse);
    double getClosest(Ray &r,int &closeObj, bool check);
};

#endif // TRACER_H
