#include "Ent.hpp"
#include "Segment.hpp"
#include "Plane.hpp"

#define DEBUG_ENT

#ifdef DEBUG_ENT
#include <iostream>
#endif

Triple Ent::orientation() {
        return Triple(cos(ang), sin(ang), 0);
}

tuple<Triple, Triple> points(Ent *e1, Ent *e2) {
        Segment *s1, *s2;
        Plane   *p1, *p2;

        if ((s1 = dynamic_cast<Segment *>(e1)) != NULL) {
                if ((s2 = dynamic_cast<Segment *>(e2)) != NULL) return points(s1, s2);
                if ((p2 = dynamic_cast<Plane   *>(e2)) != NULL) return points(s1, p2);
                return points(s1, e2);
        }
        if ((p1 = dynamic_cast<Plane *>(e1)) != NULL) {
                if ((s2 = dynamic_cast<Segment *>(e2)) != NULL) return points(p1, s2);
                if ((p2 = dynamic_cast<Plane   *>(e2)) != NULL) return points(p1, p2);
                return points(p1, e2);
        }
        if ((s2 = dynamic_cast<Segment *>(e2)) != NULL) return points(e1, s2);
        if ((p2 = dynamic_cast<Plane   *>(e2)) != NULL) return points(e1, p2);

        return make_tuple(e1->pos, e2->pos);
}

tuple<Triple, Triple> points(Segment *s, Plane *p) {
        return make_tuple(Triple(0, 0, 0), Triple(0, 0, 0));
}

tuple<Triple, Triple> points(Plane *p, Segment *s) {
        return make_tuple(Triple(0, 0, 0), Triple(0, 0, 0));
}
