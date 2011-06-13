#include "Ent.hpp"
#include "Segment.hpp"

#define DEBUG_ENT

#ifdef DEBUG_ENT
#include <iostream>
#endif

Triple Ent::orientation() {
        return Triple(cos(ang), sin(ang), 0);
}

double dist(Ent *e1, Ent *e2) {
        Segment *s1, *s2;
        if ((s1 = dynamic_cast<Segment *>(e1)) != NULL) {
                if ((s2 = dynamic_cast<Segment *>(e2)) != NULL) {
#ifdef DEBUG_ENT
                        cout << "dist(Segment, Segment)" << endl;
#endif
                        return dist(s1, s2);
                }
#ifdef DEBUG_ENT
                cout << "dist(Segment, Ent)" << endl;
#endif
                return dist(s1, e2);
        }
        if ((s2 = dynamic_cast<Segment *>(e2)) != NULL) {
#ifdef DEBUG_ENT
                cout << "dist(Segment, Ent)" << endl;
#endif
                return dist(s2, e1);
        }

#ifdef DEBUG_ENT
        cout << "dist(Ent, Ent)" << endl;
#endif

        return (e1->pos - e2->pos).length();
}
