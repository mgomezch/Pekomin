#include <cmath>

#include "LookWhereYoureGoing.hpp"
#include "Mobile.hpp"
#include "util.hpp"

#define DEBUG_LOOKWHEREYOUREGOING

#ifdef DEBUG_LOOKWHEREYOUREGOING
#include <iostream>
#endif

LookWhereYoureGoing::LookWhereYoureGoing(Mobile *character, double maxAngularVelocity, double targetRadius, double slowRadius) {
        this->character          = character;
        this->maxAngularVelocity = maxAngularVelocity;
        this->targetRadius       = targetRadius;
        this->slowRadius         = slowRadius;
}

pair<bool, double> LookWhereYoureGoing::getAngVel(unsigned int ticks) {
        pair<bool, double> steering;
        double rotation, rotationSize, targetRotation;
        Triple direction;

        steering.first = true;

        direction = 2 * atan(character->vel.length()) / M_PI;
        if (direction.length() == 0) {
                steering.first = false;
#ifdef DEBUG_LOOKWHEREYOUREGOING
                cout << "velocidad : " << direction.x << direction.y << direction.z << endl;
#endif
                return steering;
        }

        rotation = mapToRange(atan2(direction.y, direction.x)) - mapToRange(character->ang);
        if (rotation > M_PI) rotation -= 2 * M_PI;
        rotationSize = abs(rotation);

        if (rotationSize < targetRadius) {
#ifdef DEBUG_LOOKWHEREYOUREGOING
                cout << "LookWhereYoureGoing " << static_cast<void *>(this) << ": dentro de targetRadius" << endl;
#endif
                steering.second = character->vrot;
                if (abs(steering.second) > maxAngularVelocity) {
                        steering.second = maxAngularVelocity;
                }
                return steering;
        }

        targetRotation = maxAngularVelocity;
        if (rotationSize < slowRadius) {
#ifdef DEBUG_LOOKWHEREYOUREGOING
                cout << "LookWhereYoureGoing " << static_cast<void *>(this) << ": entre targetRadius y slowRadius" << endl;
#endif
                targetRotation *= rotationSize / slowRadius;
        }
#ifdef DEBUG_LOOKWHEREYOUREGOING
        else {
                cout << "LookWhereYoureGoing " << static_cast<void *>(this) << ": fuera de slowRadius" << endl;
        }
#endif
        targetRotation *= 2 * atan(200*character->vel.length()) / M_PI;
	cout << "SEXOOOOOOOO " << targetRotation << endl;
        steering.second = targetRotation * (rotation > 0 ? 1 : -1);

        return steering;
}


 
