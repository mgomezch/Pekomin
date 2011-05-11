#include "Ent.hpp"

Triple Ent::orientation() {
        return Triple(cos(ang), sin(ang), 0);
}
