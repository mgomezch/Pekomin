#include "Ent.hpp"
#include "Mobile.hpp"

double dist(Mobile *m1, Mobile *m2) {
        return dist(static_cast<Ent *>(m1), static_cast<Ent *>(m2));
}
