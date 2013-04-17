#ifndef RAY_H
#define RAY_H

#include "vector.h"
#include "point.h"

class Ray {
public:
    Vector o, d;
    Ray();
    Ray(Vector oo, Vector dd);
};

#endif // RAY_H
