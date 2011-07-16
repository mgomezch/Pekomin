#include <vector>

#include "Ent.hpp"
#include "KinematicArrive.hpp"
#include "Triple.hpp"

KinematicArrive::KinematicArrive(std::string name, Ent *character, Ent *target, double maxSpeed, double radius):
        DirectKinematicV(name),
        character(character),
        target(target),
        maxSpeed(maxSpeed),
        radius(radius)
{}

std::vector<Triple> KinematicArrive::getVel(unsigned int ticks, unsigned int delta_ticks) {
        Triple steering;
        Triple cp, tp;

        std::tie(cp, tp) = points(this->character, this->target);
        steering = tp - cp;

        if (steering.length() > radius) {
                steering /= timeToTarget;
                if (steering.length() > maxSpeed) {
                        steering.normalized();
                        steering *= maxSpeed;
                }
                return std::vector<Triple>(1, steering);
        }

        return std::vector<Triple>();
}
