#include <cmath>
#include <vector>

#include "Align.hpp"
#include "Mobile.hpp"
#include "Triple.hpp"
#include "util.hpp"

//#define DEBUG_ALIGN

#ifdef DEBUG_ALIGN
#include <iostream>
#endif

Align::Align(std::string name, Mobile *character, Mobile *target, double maxAngularVelocity, double targetRadius, double slowRadius):
        DirectKinematicA(name),
        character(character),
        target(target),
        maxAngularVelocity(maxAngularVelocity),
        targetRadius(targetRadius),
        slowRadius(slowRadius)
{}

std::vector<double> Align::getAngVel(unsigned int ticks, unsigned int delta_ticks) {
        double steering;
        double rotation, rotationSize, targetRotation;
        Triple direction;

        rotation = mapToRange(mapToRange(target->ang) - mapToRange(character->ang));
        rotationSize = abs(rotation);

        if (rotationSize < targetRadius) {
#ifdef DEBUG_ALIGN
                std::cout << "Align " << static_cast<void *>(this) << ": dentro de targetRadius" << std::endl;
#endif
                steering = target->vrot - character->vrot;
                if (abs(steering) > maxAngularVelocity) {
                        steering = maxAngularVelocity;
                }
                return std::vector<double>(1, steering);
        }

        targetRotation = maxAngularVelocity;
        if (rotationSize < slowRadius){
                targetRotation *= rotationSize / slowRadius;
#ifdef DEBUG_ALIGN
                std::cout << "Align " << static_cast<void *>(this) << ": entre targetRadius y slowRadius; targetRotation = " << targetRotation << "; rotation = " << rotation << std::endl;
#endif
        }
#ifdef DEBUG_ALIGN
        else {
                std::cout << "Align " << static_cast<void *>(this) << ": fuera de slowRadius; targetRotation = " << targetRotation << "; rotation = " << rotation << std::endl;
        }
#endif

        //targetRotation *= map_atan(20000 * target->vrot);

        steering = targetRotation * (rotation > 0 ? -1 : 1);

        return std::vector<double>(1, steering);
}
