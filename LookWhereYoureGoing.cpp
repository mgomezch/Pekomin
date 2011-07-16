#include <cmath>
#include <vector>

#include "LookWhereYoureGoing.hpp"
#include "Mobile.hpp"
#include "Triple.hpp"
#include "util.hpp"

//#define DEBUG_LOOKWHEREYOUREGOING

#ifdef DEBUG_LOOKWHEREYOUREGOING
#       include <iostream>
#endif

LookWhereYoureGoing::LookWhereYoureGoing(std::string name, Mobile *character, double maxAngularVelocity, double targetRadius, double slowRadius):
        DirectKinematicA(name),
        character(character),
        maxAngularVelocity(maxAngularVelocity),
        targetRadius(targetRadius),
        slowRadius(slowRadius)
{}

std::vector<double> LookWhereYoureGoing::getAngVel(unsigned int ticks, unsigned int delta_ticks) {
        double steering;
        double rotation, rotationSize, targetRotation;
        Triple direction;

        direction = character->vel;
        if (direction.length() == 0) {
                return std::vector<double>();
        }

        rotation = mapToRange(mapToRange(atan2(direction.y, direction.x)) - mapToRange(character->ang));
        rotationSize = abs(rotation);

        if (rotationSize < targetRadius) {
#ifdef DEBUG_LOOKWHEREYOUREGOING
                std::cout << "LookWhereYoureGoing " << static_cast<void *>(this) << ": dentro de targetRadius" << std::endl;
#endif
                steering = character->vrot;
                if (abs(steering) > maxAngularVelocity) {
                        steering = maxAngularVelocity;
                }
                return std::vector<double>(1, steering);
        }

        targetRotation = maxAngularVelocity;
        if (rotationSize < slowRadius) {
#ifdef DEBUG_LOOKWHEREYOUREGOING
                std::cout << "LookWhereYoureGoing " << static_cast<void *>(this) << ": entre targetRadius y slowRadius" << std::endl;
#endif
                targetRotation *= rotationSize / slowRadius;
        }
#ifdef DEBUG_LOOKWHEREYOUREGOING
        else {
                std::cout << "LookWhereYoureGoing " << static_cast<void *>(this) << ": fuera de slowRadius" << std::endl;
        }
#endif

        targetRotation *= map_atan(20000*character->vel.length());

#ifdef DEBUG_LOOKWHEREYOUREGOING
        std::cout << "LookWhereYoureGoing " << static_cast<void *>(this) << ": targetRotation == " << targetRotation << " after mapping vel with factor " << map_atan(200*character->vel.length()) << std::endl;
#endif

        steering = targetRotation * (rotation > 0 ? -1 : 1);

        return std::vector<double>(1, steering);
}
