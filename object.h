#ifndef OBJECT_H
#define OBJECT_H

#include "point.h"
#include "ray.h"

class Object{
public:
    Point color;
    double diffuse, specular, shiny; // need to add index of refraction

    virtual double intersect(Ray &ray);
    virtual void getReflected(Ray &ray, double t, Ray &rray, Vector &normal);
    // need to add getTransmitted(Ray &ray; double t, Ray &rray, Vector &normal);
    //virtual void getTransmitted(Ray &ray, double t, Ray &rray);
};

class Sphere: public Object {
public:
    Point origin;
    double r;
    Sphere(Point o, double r, Point colorarr, double diff, double spec, double shin);

    double intersect(Ray &ray);
    void getReflected(Ray &ray, double t, Ray &rray, Vector &normal);
    //void getTransmitted(Ray &ray, double t, Ray &rray);
};

class Plane: public Object {
public:
    Vector normal;
    double d;
    Plane(Vector n, double dd, Point colorarr, double diff, double spec, double shin);

    double intersect(Ray &ray);
    void getReflected(Ray &ray, double t, Ray &rray, Vector &n);
};

#endif // OBJECT_H
