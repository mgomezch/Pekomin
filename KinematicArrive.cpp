#include "Ent.hpp"
#include "KinematicArrive.hpp"
#include "Triple.hpp"

KinematicArrive::KinematicArrive(string name, Ent *character, Ent *target, double maxSpeed, double radius):
        DirectKinematicV(name),
        character(character),
        target(target),
        maxSpeed(maxSpeed),
        radius(radius)
{}

pair<bool, Triple> KinematicArrive::getVel(unsigned int ticks) {
        pair<bool, Triple> steering;
        Triple cp, tp;

        steering.first = false;

        tie(cp, tp) = points(this->character, this->target);
        steering.second = tp - cp;

        if (steering.second.length() > radius) {
                steering.first = true;
                steering.second /= timeToTarget;
                if (steering.second.length() > maxSpeed) {
                        steering.second.normalized();
                        steering.second *= maxSpeed;
                }
        }

        return steering;
}
