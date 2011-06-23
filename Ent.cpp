#include <cmath>

#include "Box.hpp"
#include "Ent.hpp"
#include "Segment.hpp"
#include "SurfacePlane.hpp"
#include "Triple.hpp"
#include "VolumePlane.hpp"

#define DEBUG_ENT

#ifdef DEBUG_ENT
#include <iostream>
#endif

#define DEF_POINTS_SWAPPER(T1, T2)                   \
        tuple<Triple, Triple> points(T2 *x, T1 *y) { \
                Triple a, b;                         \
                tie(b, a) = points(y, x);            \
                return make_tuple(a, b);             \
        }

#define DEF_POINTS_STUB(T1, T2)                        \
        tuple<Triple, Triple> points(T1 *x, T2 *y) {   \
                return make_tuple(Triple(), Triple()); \
        }

Ent::Ent(string name, Triple pos, double ang):
        name(name),
        pos(pos),
        ang(ang)
{}

Triple Ent::orientation() {
        return Triple(cos(ang), sin(ang), 0);
}

tuple<Triple, Triple> points(Ent *e1, Ent *e2) {
        // TODO: los comportamientos deberían ser templates para que no haga falta todo esto
        Segment      *s1, *s2;
        Box          *b1, *b2;
        SurfacePlane *f1, *f2;
        VolumePlane  *v1, *v2;

        if ((s1 = dynamic_cast<Segment *>(e1)) != NULL) {
                if ((s2 = dynamic_cast<Segment      *>(e2)) != NULL) return points(s1, s2);
                if ((b2 = dynamic_cast<Box          *>(e2)) != NULL) return points(s1, b2);
                if ((f2 = dynamic_cast<SurfacePlane *>(e2)) != NULL) return points(s1, f2);
                if ((v2 = dynamic_cast<VolumePlane  *>(e2)) != NULL) return points(s1, v2);
                return points(s1, e2);
        }
        if ((b1 = dynamic_cast<Box *>(e1)) != NULL) {
                if ((s2 = dynamic_cast<Segment      *>(e2)) != NULL) return points(b1, s2);
                if ((b2 = dynamic_cast<Box          *>(e2)) != NULL) return points(b1, b2);
                if ((f2 = dynamic_cast<SurfacePlane *>(e2)) != NULL) return points(b1, f2);
                if ((v2 = dynamic_cast<VolumePlane  *>(e2)) != NULL) return points(b1, v2);
                return points(b1, e2);
        }
        if ((f1 = dynamic_cast<SurfacePlane *>(e1)) != NULL) {
                if ((s2 = dynamic_cast<Segment      *>(e2)) != NULL) return points(f1, s2);
                if ((b2 = dynamic_cast<Box          *>(e2)) != NULL) return points(f1, b2);
                if ((f2 = dynamic_cast<SurfacePlane *>(e2)) != NULL) return points(f1, f2);
                if ((v2 = dynamic_cast<VolumePlane  *>(e2)) != NULL) return points(f1, v2);
                return points(f1, e2);
        }
        if ((v1 = dynamic_cast<VolumePlane *>(e1)) != NULL) {
                if ((s2 = dynamic_cast<Segment      *>(e2)) != NULL) return points(v1, s2);
                if ((b2 = dynamic_cast<Box          *>(e2)) != NULL) return points(v1, b2);
                if ((f2 = dynamic_cast<SurfacePlane *>(e2)) != NULL) return points(v1, f2);
                if ((v2 = dynamic_cast<VolumePlane  *>(e2)) != NULL) return points(v1, v2);
                return points(v1, e2);
        }
        if ((s2 = dynamic_cast<Segment      *>(e2)) != NULL) return points(e1, s2);
        if ((b2 = dynamic_cast<Box          *>(e2)) != NULL) return points(e1, b2);
        if ((f2 = dynamic_cast<SurfacePlane *>(e2)) != NULL) return points(e1, f2);
        if ((v2 = dynamic_cast<VolumePlane  *>(e2)) != NULL) return points(e1, v2);

        return make_tuple(e1->pos, e2->pos);
}

// TODO: implementar toda esta vaina!
DEF_POINTS_STUB(Segment     , SurfacePlane)
DEF_POINTS_STUB(Segment     , VolumePlane )
DEF_POINTS_STUB(Segment     , Box         )
DEF_POINTS_STUB(SurfacePlane, VolumePlane )
DEF_POINTS_STUB(SurfacePlane, Box         )
DEF_POINTS_STUB(VolumePlane , Box         )

DEF_POINTS_SWAPPER(Segment     , SurfacePlane)
DEF_POINTS_SWAPPER(Segment     , VolumePlane )
DEF_POINTS_SWAPPER(Segment     , Box         )
DEF_POINTS_SWAPPER(SurfacePlane, VolumePlane )
DEF_POINTS_SWAPPER(SurfacePlane, Box         )
DEF_POINTS_SWAPPER(VolumePlane , Box         )
