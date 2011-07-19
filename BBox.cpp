#include <cmath>
#include <string>

#include "BBox.hpp"
#include "Mobile.hpp"
#include "Triple.hpp"

//#define DEBUG_BOX

#ifdef DEBUG_BOX
#       include <iostream>
#       define DEBUG_BOX_PRINT(S) std::cout << "DEBUG: BBox " << reinterpret_cast<void *>(this) << ": " #S << " == " << S << std::endl;
#else
#       define DEBUG_BOX_PRINT(S)
#endif

BBox::BBox(std::string name, Triple pos, double ang, Triple vel, double vrot, double sx, double sy, double sz):
        Mobile(name, pos, ang, vel, vrot),
        sx(sx), sy(sy), sz(sz)
{}

std::tuple<Triple, Triple> points(BBox *s, Ent *e) {
        double dist, size;
        Triple r = s->pos, p = e->pos;
        Triple d = p - r;
        Triple dir;

        dir  = Triple(cos(s->ang), sin(s->ang), 0);
        dist = d.dot(dir);
        size = s->sx;
        if (dist < -size) dist = -size;
        if (size <  dist) dist =  size;
        r += dir * dist;

        dir  = Triple(-sin(s->ang), cos(s->ang), 0);
        dist = d.dot(dir);
        size = s->sy;
        if (dist < -size) dist = -size;
        if (size <  dist) dist =  size;
        r += dir * dist;

        dir  = Triple(0, 0, 1);
        dist = d.dot(dir);
        size = s->sz;
        if (dist < -size) dist = -size;
        if (size <  dist) dist =  size;
        r += dir * dist;

        return std::make_tuple(r, p);
}

std::tuple<Triple, Triple> points(Ent *x, BBox *y) {
        Triple a, b;
        std::tie(b, a) = points(y, x);
        return std::make_tuple(a, b);
}

std::tuple<Triple, Triple> points(Mobile *e, BBox *s) {
        return points(static_cast<Ent *>(e), s);
}

std::tuple<Triple, Triple> points(BBox *s, Mobile *e) {
        return points(s, static_cast<Ent *>(e));
}

std::tuple<Triple, Triple> points(BBox *s1, BBox *s2) {
        // TODO
        return std::make_tuple(Triple(), Triple());
}
