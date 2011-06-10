#include <cmath>

#include "Align.hpp"
#include "Mobile.hpp"
#include "util.hpp"

//#define DEBUG_ALIGN

#ifdef DEBUG_ALIGN
#include <iostream>
#endif

Align::Align(Mobile *character, Mobile *target, double maxAngularVelocity, double targetRadius, double slowRadius) {
        this->character          = character;
        this->target             = target;
        this->maxAngularVelocity = maxAngularVelocity;
        this->targetRadius       = targetRadius;
        this->slowRadius         = slowRadius;
}

pair<bool, double> Align::getAngVelIncr(unsigned int ticks) {
        pair<bool, double> steering;
        double rotation, rotationSize, targetRotation;
        Triple direction;

        steering.first  = true;
        steering.second = 0;

        rotation = mapToRange(target->ang) - mapToRange(character->ang);
        if (rotation > M_PI) rotation -= 2 * M_PI;
        rotationSize = abs(rotation);

        if (rotationSize < targetRadius) {
#ifdef DEBUG_ALIGN
                cout << "Align " << static_cast<void *>(this) << ": dentro de targetRadius" << endl;
#endif
                steering.second = target->vrot - character->vrot;
                if (abs(steering.second) > maxAngularVelocity) {
                        steering.second = maxAngularVelocity;
                }
                return steering;
        }

        targetRotation = maxAngularVelocity;
        if (rotationSize < slowRadius) {
                targetRotation *= rotationSize / slowRadius;
#ifdef DEBUG_ALIGN
                cout << "Align " << static_cast<void *>(this) << ": entre targetRadius y slowRadius; targetRotation = " << targetRotation << "; rotation = " << rotation << endl;
#endif
        }
#ifdef DEBUG_ALIGN
        else {
                cout << "Align " << static_cast<void *>(this) << ": fuera de slowRadius; targetRotation = " << targetRotation << "; rotation = " << rotation << endl;
        }
#endif
        if (targetRotation < 0) targetRotation = 0;

        steering.second = targetRotation * (rotation > 0 ? 1 : -1);

        return steering;
}
