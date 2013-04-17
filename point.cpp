#include <stdio.h>
#include <cmath>
#include "point.h"

Point::Point() {
	x=0; y=0; z=0;
}

Point::Point(double xx, double yy, double zz) {
	x=xx, y=yy; z=zz;
}

Point::Point(double values[]){
	x=values[0]; y=values[1]; z=values[2];
}

void Point::add(Point &a, Point &b){
	x=a.x+b.x;
	y=a.y+b.y;
	z=a.z+b.z;
}

void Point::sub(Point &a, Point &b){
	x=a.x-b.x;
	y=a.y-b.y;
	z=a.z-b.z;
}

void Point::scale(double n){
	x*=n; y*=n; z*=n;
}

void Point::negate(){
	x=-x; y=-y; z=-z;
}

void Point::print(){
	printf("[%f, %f, %f]\n", x, y, z);
}

double Point::distanceTo(Point &a){
	float tmpx = x-a.x;
	float tmpy = y-a.y;
	float tmpz = z-a.z;
	tmpx*=tmpx; tmpy*=tmpy; tmpz*=tmpz; // square them!

	return sqrt(tmpx+tmpy+tmpz);
}

Point & Point::operator=(const Point &rhs){
    x=rhs.x; y=rhs.y; z=rhs.z;
}
