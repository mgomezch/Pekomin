#include <cmath>
#include <iostream>
#include <string>
#include <sstream>

#include <cstdio>
#include <cstdlib>
#include <sysexits.h>

#include "Triple.hpp"

using namespace std;

Triple const Triple::operator+(Triple const &t) const {
        Triple r = *this;
        r.x += t.x;
        r.y += t.y;
        r.z += t.z;
        return r;
}

Triple const Triple::operator+(double const &f) const {
        Triple r = *this;
        r.x += f;
        r.y += f;
        r.z += f;
        return r;
}

Triple const Triple::operator-() const {
        Triple r = *this;
        r.x = -r.x;
        r.y = -r.y;
        r.z = -r.z;
        return r;
}

Triple const Triple::operator-(Triple const &t) const {
        Triple r = *this;
        r.x -= t.x;
        r.y -= t.y;
        r.z -= t.z;
        return r;
}

Triple const Triple::operator-(double const &f) const {
        Triple r = *this;
        r.x -= f;
        r.y -= f;
        r.z -= f;
        return r;
}

Triple const Triple::operator*(Triple const &t) const {
        Triple r = *this;
        r.x *= t.x;
        r.y *= t.y;
        r.z *= t.z;
        return r;
}

Triple const Triple::operator*(double const &f) const {
        Triple r = *this;
        r.x *= f;
        r.y *= f;
        r.z *= f;
        return r;
}

Triple const Triple::operator/(double const &f) const {
        return Triple(this->x / f, this->y / f, this->z / f);
}

Triple& Triple::operator = (double const &f) {
        this->x = f;
        this->y = f;
        this->z = f;
        return *this;
}

Triple& Triple::operator += (Triple const &t) {
        this->x += t.x;
        this->y += t.y;
        this->z += t.z;
        return *this;
}

Triple& Triple::operator += (double const &f) {
        this->x += f;
        this->y += f;
        this->z += f;
        return *this;
}

Triple& Triple::operator -= (Triple const &t) {
        this->x -= t.x;
        this->y -= t.y;
        this->z -= t.z;
        return *this;
}

Triple& Triple::operator-=(double const &f) {
        this->x -= f;
        this->y -= f;
        this->z -= f;
        return *this;
}

Triple& Triple::operator*=(double const &f) {
        this->x *= f;
        this->y *= f;
        this->z *= f;
        return *this;
}

Triple& Triple::operator/=(double const &f) {
        this->x /= f;
        this->y /= f;
        this->z /= f;
        return *this;
}

double Triple::dot(Triple const &t) const {
        return this->x*t.x + this->y*t.y + this->z*t.z;
}

Triple const Triple::cross(Triple const &t) const {
        return Triple(this->y*t.z - this->z*t.y, this->z*t.x - this->x*t.z, this->x*t.y - this->y*t.x);
}

double Triple::length() const {
        return sqrt(this->length_2());
}

double Triple::length_2() const {
        return this->x*this->x + this->y*this->y + this->z*this->z;
}

Triple const Triple::normalized() const {
        return (*this)/this->length();
}

Triple& Triple::normalize() {
        return (*this) /= this->length();
}

double Triple::ang_xy() const {
        return atan2(this->y, this->x);
}

string const Triple::to_string() const {
        stringstream str;
        str << "(" << x << ", " << y << ", " << z << ")";
        return str.str();
}
