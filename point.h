#ifndef POINT_H
#define POINT_H
class Point {
public:
	double x,y,z;

	Point();
	Point(double, double, double);
	Point(double[]);
	void add(Point &a, Point &b);
	void sub(Point &a, Point &b);
	void scale(double n);
	void negate();
	void print();
	double distanceTo(Point &a);
	Point &operator=(const Point &rhs);
};
#endif
