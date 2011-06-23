#include <cmath>

#include "Segment.hpp"
#include "Triple.hpp"

//#define DEBUG_SEGMENT

#ifdef DEBUG_SEGMENT
#       include <iostream>
#endif

Segment::Segment(string name, Triple pos, double ang, Triple vel, double vrot, Triple p1, Triple p2):
        Mobile(name, pos, ang, vel, vrot),
        p1(p1),
        p2(p2)
{}

Triple Segment::v1() {
        return this->pos + Triple(this->p1.x * cos(this->ang) - this->p1.y * sin(this->ang),
                                  this->p1.x * sin(this->ang) + this->p1.y * cos(this->ang),
                                  this->p1.z);
}

Triple Segment::v2() {
        return this->pos + Triple(this->p2.x * cos(this->ang) - this->p2.y * sin(this->ang),
                                  this->p2.x * sin(this->ang) + this->p2.y * cos(this->ang),
                                  this->p2.z);
}

tuple<Triple, Triple> points(Segment *s, Ent *e) {
        double l1, l2;
        Triple d, sv1, sv2, p;

        p   = e->pos;
        sv1 = s->v1();
        sv2 = s->v2();

        d   = sv2 - sv1;
        l2  = d.length();
        d  /= l2;
        l1 = (p - sv1).dot(d);
        if (0 <= l1 && l1 <= l2) return make_tuple(sv1 + d * l1, p);

        l1 = (p - sv1).length();
        l2 = (p - sv2).length();
        if (l1 < l2) return make_tuple(sv1, p);
        return make_tuple(sv2, p);
}

tuple<Triple, Triple> points(Ent *e, Segment *s) {
        Triple a, b;
        tie(b, a) = points(s, e);
        return make_tuple(a, b);
}

tuple<Triple, Triple> points(Mobile *e, Segment *s) {
        return points(static_cast<Ent *>(e), s);
}

tuple<Triple, Triple> points(Segment *s, Mobile *e) {
        return points(s, static_cast<Ent *>(e));
}

tuple<Triple, Triple> points(Segment *s1, Segment *s2) {
        Triple d1, d2, dc, s1v1, s1v2, s2v1, s2v2, p1, p2, ps;
        double ndc2, t, s, l1, l2;
        int i;

        s1v1 = s1->v1();
        s1v2 = s1->v2();
        s2v1 = s2->v1();
        s2v2 = s2->v2();
        d1   = (s1v2 - s1v1);
        d2   = (s2v2 - s2v1);
        l1   = d1.length();
        l2   = d2.length();
        d1  /= l1;
        d2  /= l2;
        dc   = d1.cross(d2);
        ndc2 = dc.length_2();

        if (ndc2 == 0) {
                t = d1.dot(s2v1 - s1v1);
                if (0 <= t && t <= l1) return make_tuple(s1v1 + d1 * t, s2v1);

                t = d1.dot(s2v2 - s1v1);
                if (0 <= t && t <= l1) return make_tuple(s1v1 + d1 * t, s2v2);

                s = d2.dot(s1v1 - s2v1);
                if (0 <= s && s <= l2) return make_tuple(s1v1, s2v1 + d2 * s);

                s = d2.dot(s1v2 - s2v1);
                if (0 <= s && s <= l2) return make_tuple(s1v2, s2v1 + d2 * s);

                i = 0;
                l1 = (s1v1 - s2v1).length();
                if ((l2 = (s1v1 - s2v2).length()) < l1) i = 1, l1 = l2;
                if ((l2 = (s1v2 - s2v1).length()) < l1) i = 2, l1 = l2;
                if ((l2 = (s1v2 - s2v2).length()) < l1) i = 3, l1 = l2;
                switch (i) {
                        default: // avoids warning
                        case 0: return make_tuple(s1v1, s2v1);
                        case 1: return make_tuple(s1v1, s2v2);
                        case 2: return make_tuple(s1v2, s2v1);
                        case 3: return make_tuple(s1v2, s2v2);
                }
        } else {
                ps = s2v1 - s1v1;
                t  = ps.cross(d2).dot(dc)/ndc2;
                s  = ps.cross(d1).dot(dc)/ndc2;
                if (0 <= t && t <= l1) {
                        p1 = s1v1 + d1 * t;
                        if (0 <= s && s <= l2) {
                                p2 = s2v1 + d2 * s;
                                return make_tuple(p1, p2);
                        }
                        l1 = (p1 - s2v1).length();
                        l2 = (p1 - s2v2).length();
                        if (l1 < l2) return make_tuple(p1, s2v1);
                        return make_tuple(p1, s2v2);
                }
                if (0 <= s && s <= l2) {
                        p2 = s2v1 + d2 * s;
                        l1 = (p2 - s1v1).length();
                        l2 = (p2 - s1v2).length();
                        if (l1 < l2) return make_tuple(s1v1, p2);
                        return make_tuple(s1v2, p2);
                }

                i = 0;
                l1 = (s1v1 - s2v1).length();
                if ((l2 = (s1v1 - s2v2).length()) < l1) i = 1, l1 = l2;
                if ((l2 = (s1v2 - s2v1).length()) < l1) i = 2, l1 = l2;
                if ((l2 = (s1v2 - s2v2).length()) < l1) i = 3, l1 = l2;
                switch (i) {
                        default: // avoids warning
                        case 0: return make_tuple(s1v1, s2v1);
                        case 1: return make_tuple(s1v1, s2v2);
                        case 2: return make_tuple(s1v2, s2v1);
                        case 3: return make_tuple(s1v2, s2v2);
                }
        }
}
