#include <cmath>
#include <string>

#include "Box.hpp"
#include "Mobile.hpp"
#include "Triple.hpp"

//#define DEBUG_BOX

#ifdef DEBUG_BOX
#       include <iostream>
#       define DEBUG_BOX_PRINT(S) cout << "DEBUG: Box " << reinterpret_cast<void *>(this) << ": " #S << " == " << S << endl;
#else
#       define DEBUG_BOX_PRINT(S)
#endif

Box::Box(string name, Triple pos, double ang, Triple vel, double vrot, double sx, double sy, double sz):
        Mobile(name, pos, ang, vel, vrot),
        sx(sx), sy(sy), sz(sz)
{}

tuple<Triple, Triple> points(Box *s, Ent *e) {
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

        return make_tuple(r, p);
}

tuple<Triple, Triple> points(Ent *x, Box *y) {
        Triple a, b;
        tie(b, a) = points(y, x);
        return make_tuple(a, b);
}

tuple<Triple, Triple> points(Mobile *e, Box *s) {
        return points(static_cast<Ent *>(e), s);
}

tuple<Triple, Triple> points(Box *s, Mobile *e) {
        return points(s, static_cast<Ent *>(e));
}

tuple<Triple, Triple> points(Box *s1, Box *s2) {
        // TODO
        return make_tuple(Triple(), Triple());
}
