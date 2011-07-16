#include <cmath>

#include "Triple.hpp"
#include "VolumePlane.hpp"

//#define DEBUG_VOLUMEPLANE

#ifdef DEBUG_VOLUMEPLANE
#include <iostream>
#endif

VolumePlane::VolumePlane(std::string name, Triple pos, double ang, Triple vel, double vrot, Triple pp, Triple n):
        Plane(name, pos, ang, vel, vrot, pp, n)
{}

std::tuple<Triple, Triple> points(VolumePlane *p, Ent *e) {
        Triple ep = e->pos, pn = p->normal();
        double d = pn.dot(ep - p->point());

        if (d <= 0) return std::make_tuple(ep, ep);
        return std::make_tuple(ep - pn * d, ep);
}

std::tuple<Triple, Triple> points(Ent *e, VolumePlane *p) {
        Triple a, b;
        std::tie(b, a) = points(p, e);
        return std::make_tuple(a, b);
}

std::tuple<Triple, Triple> points(Mobile *e, VolumePlane *p) {
        return points(static_cast<Ent *>(e), p);
}

std::tuple<Triple, Triple> points(VolumePlane *p, Mobile *e) {
        return points(p, static_cast<Ent *>(e));
}

std::tuple<Triple, Triple> points(VolumePlane *p1, VolumePlane *p2) {
        Triple n1  = p1->normal();
        Triple n2  = p2->normal();
        Triple pp1 = p1->point();
        Triple pp2 = p2->point();

        Triple n1cn2, r;
        double c1, c2, cd, h1, h2;
        double n1dn2 = p1->normal().dot(p2->normal());

        if (n1dn2 == -1) return std::make_tuple(pp1, pp1 + n1 * abs(n1.dot(pp2 - pp1)));
        if (n1dn2 ==  1) {
                n1 = (pp1 + pp2)/2.0;
                return std::make_tuple(n1, n1);
        }

        n1cn2 = n1.cross(n2);
        h1 = n1.dot(pp1);
        h2 = n2.dot(pp2);
        cd = 1 - n1dn2 * n1dn2;
        c1 = (h1 - h2 * n1dn2)/cd;
        c2 = (h2 - h1 * n1dn2)/cd;
        r = (pp1 + pp2)/2.0;
        pp1 = n1*c1 + n2*c2;
        r = pp1 + n1cn2 * n1cn2.dot(r - pp1);
        return std::make_tuple(r, r);
}
