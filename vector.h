#ifndef VECTOR_H
#define VECTOR_H

#include "point.h"
class Vector: public Point {
public:
    Vector();
    Vector(double, double, double);
    Vector(double[]);
    void cross(Vector &a, Vector &b);
    double dot(Vector &b);
    double lengthSquared();
    double length();
    void normalize();
    Vector& operator=(const Vector &rhs);
};
#endif
