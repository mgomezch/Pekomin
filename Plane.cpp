#include <cmath>

#include "Plane.hpp"

//#define DEBUG_PLANE

#ifdef DEBUG_PLANE
#include <iostream>
#endif

Triple Plane::point() {
        return this->pos + Triple(this->pp.x * cos(this->ang) - this->pp.y * sin(this->ang),
                                  this->pp.x * sin(this->ang) + this->pp.y * cos(this->ang),
                                  this->pp.z);
}

Triple Plane::normal() {
        return Triple(this->n.x * cos(this->ang) - this->n.y * sin(this->ang),
                      this->n.x * sin(this->ang) + this->n.y * cos(this->ang),
                      this->n.z);
}

tuple<Triple, Triple> points(Plane *p, Ent *e) {
        Triple ep = e->pos, pn = p->normal();
        return make_tuple(ep - pn * (ep - p->point()).dot(pn), ep);
}

tuple<Triple, Triple> points(Ent *e, Plane *p) {
        Triple a, b;
        tie(b, a) = points(p, e);
        return make_tuple(a, b);
}

tuple<Triple, Triple> points(Mobile *e, Plane *p) {
        return points(static_cast<Ent *>(e), p);
}

tuple<Triple, Triple> points(Plane *p, Mobile *e) {
        return points(p, static_cast<Ent *>(e));
}

tuple<Triple, Triple> points(Plane *p1, Plane *p2) {
        Triple n1  = p1->normal();
        Triple n2  = p2->normal();
        Triple pp1 = p1->point();
        Triple pp2 = p2->point();

        Triple n1cn2, r;
        double c1, c2, cd, h1, h2;
        double n1dn2 = p1->normal().dot(p2->normal());

        if (n1dn2 == 1) return make_tuple(pp1, pp1 + n1 * abs(n1.dot(pp2 - pp1)));

        n1cn2 = n1.cross(n2);
        h1 = n1.dot(pp1);
        h2 = n2.dot(pp2);
        cd = 1 - n1dn2 * n1dn2;
        c1 = (h1 - h2 * n1dn2)/cd;
        c2 = (h2 - h1 * n1dn2)/cd;
        r = (pp1 + pp2)/2.0;
        pp1 = n1*c1 + n2*c2;
        r = pp1 + n1cn2 * n1cn2.dot(r - pp1);
        return make_tuple(r, r);
}
