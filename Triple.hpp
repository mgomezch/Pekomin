#ifndef TRIPLE_HPP
#define TRIPLE_HPP

#include <string>

class Triple {
        public:
                double x, y, z;

                Triple() : x(0), y(0), z(0) {}
                Triple(double K) : x(K), y(K), z(K) {}
                Triple(double X, double Y, double Z) : x(X), y(Y), z(Z) {}
                Triple  operator + (Triple);
                Triple  operator + (double);
                Triple  operator - ();
                Triple  operator - (Triple);
                Triple  operator - (double);
                Triple  operator * (Triple);
                Triple  operator * (double);
                Triple  operator / (double);
                Triple& operator = (double);
                Triple& operator +=(const Triple &);
                Triple& operator +=(double);
                Triple& operator -=(const Triple &);
                Triple& operator -=(double);
                Triple& operator *=(double);
                Triple& operator /=(double);
                Triple& normalize();
                double dot(Triple t);
                Triple cross(Triple t);
                double length();
                double length_2();
                Triple normalized();
                double ang_xy();
                std::string to_string();
};

#endif
