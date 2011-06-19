#include "Ent.hpp"
#include "Mobile.hpp"

tuple<Triple, Triple> points(Ent *e, Mobile *m) {
        return points(e, static_cast<Ent *>(m));
}

tuple<Triple, Triple> points(Mobile *m, Ent *e) {
        return points(static_cast<Ent *>(m), e);
}

tuple<Triple, Triple> points(Mobile *m1, Mobile *m2) {
        return points(static_cast<Ent *>(m1), static_cast<Ent *>(m2));
}
