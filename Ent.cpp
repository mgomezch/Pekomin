#include "Ent.hpp"
#include "Segment.hpp"

#define DEBUG_ENT

#ifdef DEBUG_ENT
#include <iostream>
#endif

Triple Ent::orientation() {
        return Triple(cos(ang), sin(ang), 0);
}

tuple<Triple, Triple> points(Ent *e1, Ent *e2) {
        Segment *s1, *s2;

        if ((s1 = dynamic_cast<Segment *>(e1)) != NULL) {
                if ((s2 = dynamic_cast<Segment *>(e2)) != NULL) {
                        return points(s1, s2);
                }
                return points(s1, e2);
        }
        if ((s2 = dynamic_cast<Segment *>(e2)) != NULL) {
                return points(s2, e1);
        }

        return make_tuple(e1->pos, e2->pos);
}
