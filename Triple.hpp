#ifndef _TRIPLE_HPP
#define _TRIPLE_HPP

#include <math.h>
#include <stdio.h>

using namespace std;

class Triple {
	public:
		double x, y, z;

	Triple() : x(0), y(0), z(0) {}
	Triple(double X, double Y, double Z) : x(X), y(Y), z(Z) {}
	Triple& operator+(const Triple &t);
	Triple& operator+(double f);
	Triple& operator-();
	Triple& operator-(const Triple &t);
	Triple& operator-(double f);
	Triple& operator*(const Triple &t);
	Triple& operator*(const double f);
	Triple& operator/(double f);
	Triple& operator=(double f);
	Triple& operator+=(const Triple &t);
	Triple& operator+=(double f);
	Triple& operator-=(const Triple &t);
	Triple& operator-=(double f);
	Triple& operator*=(const double f);
	Triple& operator/=(const double f);
	double dot(const Triple &t);
	Triple& cross(const Triple &t);
	double length();
	double length_2();
	Triple& normalized();
	void normalize();
	void printInfo();
	
};

typedef Triple Vector;
typedef Triple Punto;

#endif