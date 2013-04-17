#include <cmath>
#include <iostream>
#include "object.h"

using namespace std;

 double Object::intersect(Ray &ray){ return 0.0; }
 void Object::getReflected(Ray &ray, double t, Ray &rray, Vector &normal){}
 //void getTransmitted(Ray &ray, double t, Ray &rray){}

Sphere::Sphere(Point o, double rr, Point colorarr, double diff, double spec, double shin){
    origin=o;
    r=rr;
    color = colorarr;
    diffuse = diff; specular=spec, shiny = shin;
}

double Sphere::intersect(Ray &ray){
    double B, C, t0, t1, disc;
    Vector dist;
    dist.sub(ray.o, origin);
    B=ray.d.dot(dist)*2.0;

    C=dist.dot(dist)-r*r;

    disc = B*B - 4.0*C;

    if( disc<= 0)
        return -1;

    disc = sqrt(disc);

    t0 = (-B-disc)/2.0;
    if(t0>0)
        return t0;

    t1 = (-B+disc)/2.0;

    return t1;
}

void Sphere::getReflected(Ray &ray, double t, Ray &rray, Vector &normal){
    double dot;
    Vector n2;

    rray.o = ray.d;
    rray.o.scale(t);
    rray.o.add(rray.o,ray.o);

    normal.sub(rray.o, origin);
    normal.normalize();
    n2=normal;

    dot = 2*ray.d.dot(n2);
    n2.scale(dot);
    rray.d.sub(ray.d, n2);
    rray.d.normalize();
}

Plane::Plane(Vector n, double dd, Point colorarr, double diff, double spec, double shin){
    n.normalize();
    normal=n;
    d=dd;
    color=colorarr;
    diffuse=diff; specular=spec; shiny=shin;
}

double Plane::intersect(Ray &ray){
    double ndotd = normal.dot(ray.d);
    if( ndotd != 0)
        return -(normal.dot(ray.o)+d)/ndotd;
    return -1.0;
}

void Plane::getReflected(Ray &ray, double t, Ray &rray, Vector &n){
    Vector n2;
    rray.o=ray.d;
    rray.o.scale(t);
    rray.o.add(rray.o, ray.o);

    n2=normal;

    n2.scale(2.0*ray.d.dot(n2));
    rray.d.sub(ray.d, n2);

    n=normal;
}

//void Sphere::getTransmitted(Ray &ray, double t, Ray &rray){} //TODO
