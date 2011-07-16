#ifndef KINEMATICARRIVE_HPP
#define KINEMATICARRIVE_HPP

#include <vector>

#include "DirectKinematicV.hpp"
#include "Triple.hpp"

class Ent;

class KinematicArrive : public virtual DirectKinematicV { // TODO: "Kinematic_______" no debería ser DirectKinematic!
        public:
                Ent *character;
                Ent *target;
                double maxSpeed;
                double radius;

                static const double timeToTarget = 0.25;

                KinematicArrive(std::string name, Ent *character, Ent *target, double maxSpeed, double radius);

                virtual std::vector<Triple> getVel(unsigned int ticks, unsigned int delta_ticks);
};

#endif
