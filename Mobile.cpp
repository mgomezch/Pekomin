#include "Ent.hpp"
#include "Mobile.hpp"

Mobile::Mobile(std::string name, Triple pos, double ang, Triple vel, double vrot):
        Ent(name, pos, ang),
        vel(vel),
        vrot(vrot),
        new_vel(vel),
        new_vrot(vrot),
        active(true)
{}

void Mobile::update() {
        this->Ent::update();
        this->vel  = this->new_vel;
        this->vrot = this->new_vrot;
}

std::tuple<Triple, Triple> points(Ent *e, Mobile *m) {
        return points(e, static_cast<Ent *>(m));
}

std::tuple<Triple, Triple> points(Mobile *m, Ent *e) {
        return points(static_cast<Ent *>(m), e);
}

std::tuple<Triple, Triple> points(Mobile *m1, Mobile *m2) {
        return points(static_cast<Ent *>(m1), static_cast<Ent *>(m2));
}
