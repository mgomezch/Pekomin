#include "Box.hpp"

//#define DEBUG_BOX

#ifdef DEBUG_BOX
#include <iostream>
#endif

tuple<Triple, Triple> points(Box *s, Ent *e) {
        double dist, size;
        Triple r = s->pos, p = e->pos;
        Triple d = p - r;
        Triple dir;

        dir  = Triple(cos(s->ang), sin(s->ang), 0);
        dist = d.dot(dir);
        size = s->sx;
        if (-size < dist) dist = -size;
        if ( dist < size) dist =  size;
        r += dir * dist;

        dir  = Triple(-sin(s->ang), cos(s->ang), 0);
        dist = d.dot(dir);
        size = s->sy;
        if (-size < dist) dist = -size;
        if ( dist < size) dist =  size;
        r += dir * dist;

        dir  = Triple(0, 0, 1);
        dist = d.dot(dir);
        size = s->sz;
        if (-size < dist) dist = -size;
        if ( dist < size) dist =  size;
        r += dir * dist;

        return make_tuple(r, p);
}

tuple<Triple, Triple> points(Ent *e, Box *s) {
        Triple a, b;
        tie(b, a) = points(s, e);
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
