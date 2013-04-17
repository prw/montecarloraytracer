#include <cmath>
#include "vector.h"

Vector::Vector():Point(){}

Vector::Vector(double xx, double yy, double zz):Point(xx, yy, zz){}
Vector::Vector(double vals[]):Point(vals){}

void Vector::cross(Vector &a, Vector &b){
    x=a.y*b.z - a.z*b.y;
    y=a.z*b.x - a.x*b.z;
    z=a.x*b.y - a.y*b.x;
}

double Vector::dot(Vector &b){
    return x*b.x+y*b.y+z*b.z;
}

double Vector::lengthSquared(){
    return x*x+y*y+z*z;
}

double Vector::length(){
    return sqrt(lengthSquared());
}

void Vector::normalize(){
    double norm = length();
    x/=norm; y/=norm; z/=norm;
}

Vector &Vector::operator=(const Vector &rhs){
    x=rhs.x; y=rhs.y; z=rhs.z;
    return *this;
}
