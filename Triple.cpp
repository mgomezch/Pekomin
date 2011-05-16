#include "Triple.hpp"

Triple Triple::operator+(Triple t) {
        Triple r = *this;
        r.x += t.x;
        r.y += t.y;
        r.z += t.z;
        return r;
}

Triple Triple::operator+(double f) {
        Triple r = *this;
        r.x += f;
        r.y += f;
        r.z += f;
        return r;
}

Triple Triple::operator-() {
        Triple r = *this;
        r.x = -r.x;
        r.y = -r.y;
        r.z = -r.z;
        return r;
}

Triple Triple::operator-(Triple t) {
        Triple r = *this;
        r.x -= t.x;
        r.y -= t.y;
        r.z -= t.z;
        return r;
}

Triple Triple::operator-(double f) {
        Triple r = *this;
        r.x -= f;
        r.y -= f;
        r.z -= f;
        return r;
}

Triple Triple::operator*(Triple t) {
        Triple r = *this;
        r.x *= t.x;
        r.y *= t.y;
        r.z *= t.z;
        return r;
}

Triple Triple::operator*(double f) {
        Triple r = *this;
        r.x *= f;
        r.y *= f;
        r.z *= f;
        return r;
}

Triple Triple::operator/(double f) {
        Triple r = *this;
        r.x /= f;
        r.y /= f;
        r.z /= f;
        return r;
}

Triple& Triple::operator=(double f) {
        this->x = f;
        this->y = f;
        this->z = f;
        return *this;
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

Triple& Triple::operator*=(double f) {
        this->x *= f;
        this->y *= f;
        this->z *= f;
        return *this;
}

Triple& Triple::operator/=(double f) {
        this->x /= f;
        this->y /= f;
        this->z /= f;
        return *this;
}

double Triple::dot(Triple t) {
        return this->x*t.x + this->y*t.y + this->z*t.z;
}

Triple Triple::cross(Triple t) {
        Triple r = *this;
        r.x = this->y*t.z - this->z*t.y;
        r.y = this->z*t.x - this->x*t.z;
        r.z = this->x*t.y - this->y*t.x;
        return r;
}

double Triple::length() {
        return sqrt(length_2());
}

double Triple::length_2() {
        return this->x*this->x + this->y*this->y + this->z*this->z;
}

Triple Triple::normalized() {
        return (*this) / length();
}

Triple& Triple::normalize() {
        double l = length();
        this->x /= l;
        this->y /= l;
        this->z /= l;
        return *this;
}

void Triple::print() {
        printf("(%f, %f, %f)", x, y, z);
}
