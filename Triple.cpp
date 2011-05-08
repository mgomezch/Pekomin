#include "Triple.hpp"

Triple& Triple::operator+(const Triple &t) {
        this->x += t.x;
        this->y += t.y;
        this->z += t.z;
        return *this;
//      return *(new Triple(this->x+t.x, this->y+t.y, this->z+t.z));
}

Triple& Triple::operator+(double f) {
        this->x+f;
        this->y+f;
        this->z+f;
        return *this;
//      return *(new Triple(this->x+f, this->y+f, this->z+f));
}

Triple& Triple::operator-() {
        -this->x;
        -this->y;
        -this->z;
        return *this;
//      return *(new Triple(-this->x, -this->y, -this->z));
}

Triple& Triple::operator-(const Triple &t) {
        this->x-t.x;
        this->y-t.y;
        this->z-t.z;
        return *this;
//      return *(new Triple(this->x-t.x, this->y-t.y, this->z-t.z));
}

Triple& Triple::operator-(double f) {
        this->x-f;
        this->y-f;
        this->z-f;
        return *this;
//      return *(new Triple(this->x-f, this->y-f, this->z-f));
}

Triple& Triple::operator*(const Triple &t) {
        this->x*t.x;
        this->y*t.y;
        this->z*t.z;
        return *this;
//      return *(new Triple(this->x*t.x, this->y*t.y, this->z*t.z));
}

Triple& Triple::operator*(double f) {
        this->x*f;
        this->y*f;
        this->z*f;
        return *this;
//      return *(new Triple(this->x*f, this->y*f, this->z*f));
}

Triple& Triple::operator/(double f) {
        double invf = 1.0/f;
        this->x*invf;
        this->y*invf;
        this->z*invf;
        return *this;
//      return *(new Triple(this->x*invf, this->y*invf, this->z*invf));
}

Triple& Triple::operator+=(const Triple &t) {
        this->x += t.x;
        this->y += t.y;
        this->z += t.z;
        return *this;
}

Triple& Triple::operator+=(double f) {
        this->x += f;
        this->y += f;
        this->z += f;
        return *this;
}

Triple& Triple::operator-=(const Triple &t) {
        this->x -= t.x;
        this->y -= t.y;
        this->z -= t.z;
        return *this;
}

Triple& Triple::operator-=(double f) {
        this->x -= f;
        this->y -= f;
        this->z -= f;
        return *this;
}

Triple& Triple::operator*=(const double f) {
        this->x *= f;
        this->y *= f;
        this->z *= f;
        return *this;
}

Triple& Triple::operator/=(const double f) {
        double invf = 1.0/f;
        this->x *= invf;
        this->y *= invf;
        this->z *= invf;
        return *this;
}

double Triple::dot(const Triple &t) {
        return this->x*t.x + this->y*t.y + this->z*t.z;
}

Triple& Triple::cross(const Triple &t) {
        this->y*t.z - this->z*t.y;
        this->z*t.x - this->x*t.z;
        this->x*t.y - this->y*t.x;
        return *this;
//      return *(new Triple(this->y*t.z - this->z*t.y, this->z*t.x - this->x*t.z, this->x*t.y - this->y*t.x));
}

double Triple::length() {
        return sqrt(length_2());
}

double Triple::length_2() {
        return this->x*this->x + this->y*this->y + this->z*this->z;
}

Triple& Triple::normalized() {
        return (*this) / length();
}

void Triple::normalize() {
        double l = length();
        double invl = 1/l;
        this->x *= invl;
        this->y *= invl;
        this->z *= invl;
}

void Triple::printInfo() {
        printf("x = %f, y = %f, z = %f\n", x, y, z);
}

