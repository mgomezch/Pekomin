#include <cmath>
#include <vector>

#include "Face.hpp"
#include "Mobile.hpp"
#include "Triple.hpp"
#include "util.hpp"

//#define DEBUG_FACE

#ifdef DEBUG_FACE
#include <iostream>
#endif

Face::Face(std::string name, Mobile *character, Mobile *target, double maxAngularVelocity, double targetRadius, double slowRadius):
        KinematicA(name),
        character(character),
        target(target),
        maxAngularVelocity(maxAngularVelocity),
        targetRadius(targetRadius),
        slowRadius(slowRadius)
{}

std::vector<double> Face::getAngVelIncr(unsigned int ticks, unsigned int delta_ticks) {
        double steering;
        double rotation, rotationSize, targetRotation;
        Triple direction;
        Triple cp, tp;

        std::tie(cp, tp) = points(this->character, this->target);
        direction = tp - cp;
        rotation = mapToRange(atan2(direction.y, direction.x) - character->ang);
        //if (rotation > M_PI) rotation -= 2 * M_PI;
        rotationSize = abs(rotation);

        if (rotationSize < targetRadius) {
#ifdef DEBUG_FACE
                std::cout << "Face " << static_cast<void *>(this) << ": dentro de targetRadius" << std::endl;
#endif
                steering = target->vrot - character->vrot;
                if (abs(steering) > maxAngularVelocity) {
                        steering = maxAngularVelocity;
                }
                return std::vector<double>(1, steering);
        }

        targetRotation = maxAngularVelocity; // - target->vrot;
        if (rotationSize < slowRadius) {
#ifdef DEBUG_FACE
                std::cout << "Face " << static_cast<void *>(this) << ": entre targetRadius y slowRadius" << std::endl;
#endif
                targetRotation *= rotationSize / slowRadius;
        }
#ifdef DEBUG_FACE
        else {
                std::cout << "Face " << static_cast<void *>(this) << ": fuera de slowRadius" << std::endl;
        }
#endif
        //if (targetRotation < 0) targetRotation = 0;

        steering = targetRotation * (rotation > 0 ? -1 : 1);

        return std::vector<double>(1, steering);
}
