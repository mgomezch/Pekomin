#include "Ent.hpp"

Triple Ent::orientation() {
        Triple v;
        v.x = cos(ang);
        v.y = sin(ang);
        v.z = 0;

        return v;
}
