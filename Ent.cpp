#include "Ent.hpp"

Triple Ent::orientation() {
        return Triple(cos(ang), sin(ang), 0);
}

double dist(Ent &e1, Ent &e2) {
        return (e1.pos - e2.pos).length();
}
