#include "Segment.hpp"

Triple Segment::v1() {
        // TODO: rotate w.r.t. center
        return this->p1;
}

Triple Segment::v2() {
        // TODO: rotate w.r.t. center
        return this->p2;
}

double dist(Segment &s, Ent &e) {
        double l1, l2;
        Triple d, sv1, sv2, p;

        p = e.pos;
        sv1 = s.v1();
        sv2 = s.v2();

        d   = sv2 - sv1;
        l2  = d.length();
        d  /= l2;
        l1 = (p - sv1).dot(d);
        if (0 <= l1 && l1 <= l2) return (p - (sv1 + d * l1)).length();

        l1 = (p - sv1).length();
        l2 = (p - sv2).length();
        if (l1 < l2) return l1;
        return l2;
}

double dist(Ent &e, Segment &s) {
        return dist(s, e);
}

double dist(Segment &s1, Segment &s2) {
        // TODO: si se intersectan, return 0
        Triple d1, d2, dc, s1v1, s1v2, s2v1, s2v2, p1, p2, ps;
        double ndc2, t, s, l1, l2;

        s1v1 = s1.v1();
        s1v2 = s1.v2();
        s2v1 = s2.v1();
        s2v2 = s2.v2();
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
                if (0 <= t && t <= l1) return (s2v1 - (s1v1 + d1 * t)).length();

                t = d1.dot(s2v2 - s1v1);
                if (0 <= t && t <= l1) return (s2v2 - (s1v1 + d1 * t)).length();

                s = d2.dot(s1v1 - s2v1);
                if (0 <= s && s <= l2) return (s1v1 - (s2v1 + d2 * s)).length();

                s = d2.dot(s1v2 - s2v1);
                if (0 <= s && s <= l2) return (s1v2 - (s2v1 + d2 * s)).length();

                l1 = (s1v1 - s2v1).length();
                if ((l2 = (s1v1 - s2v2).length()) < l1) l1 = l2;
                if ((l2 = (s1v2 - s2v1).length()) < l1) l1 = l2;
                if ((l2 = (s1v2 - s2v2).length()) < l1) l1 = l2;
                return l1;
        } else {
                ps = s2v1 - s1v1;
                t  = ps.cross(d2).dot(dc)/ndc2;
                s  = ps.cross(d1).dot(dc)/ndc2;
                if (0 <= t && t <= l1) {
                        p1 = s1v1 + d1 * t;
                        if (0 <= s && s <= l2) {
                                p2 = s2v1 + d2 * s;
                                return (p2 - p1).length();
                        }
                        l1 = (p1 - s2v1).length();
                        l2 = (p1 - s2v2).length();
                        if (l1 < l2) return l1;
                        return l2;
                }
                if (0 <= s && s <= l2) {
                        p2 = s2v1 + d2 * s;
                        l1 = (p1 - s2v1).length();
                        l2 = (p1 - s2v2).length();
                        if (l1 < l2) return l1;
                        return l2;
                }
                l1 = (s1v1 - s2v1).length();
                if ((l2 = (s1v1 - s2v2).length()) < l1) l1 = l2;
                if ((l2 = (s1v2 - s2v1).length()) < l1) l1 = l2;
                if ((l2 = (s1v2 - s2v2).length()) < l1) l1 = l2;
                return l1;
        }
}

Triple project(Triple r1, Triple r2, Triple p) {
        Triple dir = (r2 - r1).normalized();
        return r1 + dir * (p - r1).dot(dir);
}

double line_point_distance(Triple r1, Triple r2, Triple p) {
        return (p - project(r1, r2, p)).length();
}
