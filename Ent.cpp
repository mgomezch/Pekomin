#include "Ent.hpp"
#include "Segment.hpp"
#include "SurfacePlane.hpp"

#define DEBUG_ENT

#ifdef DEBUG_ENT
#include <iostream>
#endif

Triple Ent::orientation() {
        return Triple(cos(ang), sin(ang), 0);
}

tuple<Triple, Triple> points(Ent *e1, Ent *e2) {
        // TODO: VolumePlane
        // TODO: Box
        Segment      *s1, *s2;
        SurfacePlane *p1, *p2;

        if ((s1 = dynamic_cast<Segment *>(e1)) != NULL) {
                if ((s2 = dynamic_cast<Segment      *>(e2)) != NULL) return points(s1, s2);
                if ((p2 = dynamic_cast<SurfacePlane *>(e2)) != NULL) return points(s1, p2);
                return points(s1, e2);
        }
        if ((p1 = dynamic_cast<SurfacePlane *>(e1)) != NULL) {
                if ((s2 = dynamic_cast<Segment      *>(e2)) != NULL) return points(p1, s2);
                if ((p2 = dynamic_cast<SurfacePlane *>(e2)) != NULL) return points(p1, p2);
                return points(p1, e2);
        }
        if ((s2 = dynamic_cast<Segment      *>(e2)) != NULL) return points(e1, s2);
        if ((p2 = dynamic_cast<SurfacePlane *>(e2)) != NULL) return points(e1, p2);

        return make_tuple(e1->pos, e2->pos);
}

tuple<Triple, Triple> points(Segment *s, SurfacePlane *p) {
//      Triple sv1 = s->v1();
//      Triple sv2 = s->v2();
//      double d1, d2;

//      d1 = sv1;
        return make_tuple(Triple(0, 0, 0), Triple(0, 0, 0));
}

tuple<Triple, Triple> points(SurfacePlane *p, Segment *s) {
        Triple a, b;
        tie(b, a) = points(s, p);
        return make_tuple(a, b);
}
