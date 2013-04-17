#ifndef LIGHT_H
#define LIGHT_H
#include "point.h"
class Light { // this can hopefully become more sophisticated
public:
    Point p;
    Point color;
    Light(double px, double py, double pz, double cr, double cg, double cb);
};

#endif // LIGHT_H
