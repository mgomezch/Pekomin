#include <cmath>

#include "BBox.hpp"
#include "Ent.hpp"
#include "Segment.hpp"
#include "SurfacePlane.hpp"
#include "Triple.hpp"
#include "VolumePlane.hpp"

#define DEBUG_ENT

#ifdef DEBUG_ENT
#       include <iostream>
#endif

#define DEF_POINTS_SWAPPER(T1, T2)                                                  \
        const std::tuple<const Triple, const Triple> points(const T2 * const x, const T1 * const y) { \
                Triple a, b;                                                        \
                std::tie(b, a) = points(y, x);                                      \
                return std::make_tuple(a, b);                                       \
        }

#ifdef DEBUG_ENT
#       define DEF_POINTS_STUB(T1, T2)                                                                                       \
                const std::tuple<Triple, Triple> points(T1 *x, T2 *y) {                                                      \
                        std::cerr << "WARNING: using unimplemented points() function between " #T1 " and " #T2 << std::endl; \
                        return std::make_tuple(Triple(), Triple());                                                          \
                }
#else
#       define DEF_POINTS_STUB(T1, T2)                                              \
                const std::tuple<const Triple, const Triple> points(T1 *x, T2 *y) { \
                        return std::make_tuple(Triple(), Triple());                 \
                }
#endif

Ent::Ent(std::string name, Triple pos, double ang):
        name(name),
        pos(pos),
        ang(ang),
        normals(std::vector<Triple>()),
        collides(false),
        dead(false),
        new_pos(pos),
        new_ang(ang)
{}

Ent::~Ent() {}

void Ent::update() {
        this->new_pos = this->pos;
        this->new_ang = this->ang;
}

const Triple Ent::orientation() const {
        return Triple(cos(ang), sin(ang), 0);
}

const std::tuple<const Triple, const Triple> points(const Ent * const e1, const Ent * const e2) {
        // TODO: los comportamientos deberían ser templates para que no haga falta todo esto
        const Segment      *s1, *s2;
        const BBox          *b1, *b2;
        const SurfacePlane *f1, *f2;
        const VolumePlane  *v1, *v2;

        if ((s1 = dynamic_cast<const Segment * const>(e1)) != NULL) {
                if ((s2 = dynamic_cast<const Segment      * const>(e2)) != NULL) return points(s1, s2);
                if ((b2 = dynamic_cast<const BBox          * const>(e2)) != NULL) return points(s1, b2);
                if ((f2 = dynamic_cast<const SurfacePlane * const>(e2)) != NULL) return points(s1, f2);
                if ((v2 = dynamic_cast<const VolumePlane  * const>(e2)) != NULL) return points(s1, v2);
                return points(s1, e2);
        }
        if ((b1 = dynamic_cast<const BBox * const>(e1)) != NULL) {
                if ((s2 = dynamic_cast<const Segment      * const>(e2)) != NULL) return points(b1, s2);
                if ((b2 = dynamic_cast<const BBox          * const>(e2)) != NULL) return points(b1, b2);
                if ((f2 = dynamic_cast<const SurfacePlane * const>(e2)) != NULL) return points(b1, f2);
                if ((v2 = dynamic_cast<const VolumePlane  * const>(e2)) != NULL) return points(b1, v2);
                return points(b1, e2);
        }
        if ((f1 = dynamic_cast<const SurfacePlane * const>(e1)) != NULL) {
                if ((s2 = dynamic_cast<const Segment      * const>(e2)) != NULL) return points(f1, s2);
                if ((b2 = dynamic_cast<const BBox          * const>(e2)) != NULL) return points(f1, b2);
                if ((f2 = dynamic_cast<const SurfacePlane * const>(e2)) != NULL) return points(f1, f2);
                if ((v2 = dynamic_cast<const VolumePlane  * const>(e2)) != NULL) return points(f1, v2);
                return points(f1, e2);
        }
        if ((v1 = dynamic_cast<const VolumePlane * const>(e1)) != NULL) {
                if ((s2 = dynamic_cast<const Segment      * const>(e2)) != NULL) return points(v1, s2);
                if ((b2 = dynamic_cast<const BBox          * const>(e2)) != NULL) return points(v1, b2);
                if ((f2 = dynamic_cast<const SurfacePlane * const>(e2)) != NULL) return points(v1, f2);
                if ((v2 = dynamic_cast<const VolumePlane  * const>(e2)) != NULL) return points(v1, v2);
                return points(v1, e2);
        }
        if ((s2 = dynamic_cast<const Segment      * const>(e2)) != NULL) return points(e1, s2);
        if ((b2 = dynamic_cast<const BBox          * const>(e2)) != NULL) return points(e1, b2);
        if ((f2 = dynamic_cast<const SurfacePlane * const>(e2)) != NULL) return points(e1, f2);
        if ((v2 = dynamic_cast<const VolumePlane  * const>(e2)) != NULL) return points(e1, v2);

        return std::make_tuple(e1->pos, e2->pos);
}

void Ent::addNormal(const Triple &n) {
        if (this->collides) this->normals.push_back(n);
}

void Ent::collide() {
        if (this->collides) {
                decltype(this->pos    ) &pos = this->pos;
                decltype(this->normals) &normals = this->normals;
                const int n = normals.size();
                for (int i = 0; i < n; ++i) {
                        pos += normals[i];
                }
        }
        normals.clear();
}

// TODO: implementar toda esta vaina!
DEF_POINTS_STUB(Segment     , SurfacePlane)
DEF_POINTS_STUB(Segment     , VolumePlane )
DEF_POINTS_STUB(Segment     , BBox         )
DEF_POINTS_STUB(SurfacePlane, VolumePlane )
DEF_POINTS_STUB(SurfacePlane, BBox         )
DEF_POINTS_STUB(VolumePlane , BBox         )

DEF_POINTS_SWAPPER(Segment     , SurfacePlane)
DEF_POINTS_SWAPPER(Segment     , VolumePlane )
DEF_POINTS_SWAPPER(Segment     , BBox         )
DEF_POINTS_SWAPPER(SurfacePlane, VolumePlane )
DEF_POINTS_SWAPPER(SurfacePlane, BBox         )
DEF_POINTS_SWAPPER(VolumePlane , BBox         )
