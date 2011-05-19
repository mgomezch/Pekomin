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

tuple<bool, Triple, double> Align::getVelIncr(unsigned int ticks) {
        tuple<bool, Triple, double> steering;
        double rotation, rotationSize, targetRotation;
        Triple direction;

        get<0>(steering) = true;
        get<1>(steering) = 0;

        rotation = mapToRange(target->ang) - mapToRange(character->ang);
        if (rotation > M_PI) rotation -= 2 * M_PI;
        rotationSize = abs(rotation);

        if (rotationSize < targetRadius) {
#ifdef DEBUG_ALIGN
                cout << "Align " << static_cast<void *>(this) << ": dentro de targetRadius" << endl;
#endif
                get<2>(steering) = target->vrot - character->vrot;
                if (abs(get<2>(steering)) > maxAngularVelocity) {
                        get<2>(steering) = maxAngularVelocity;
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

        get<2>(steering) = targetRotation * (rotation > 0 ? 1 : -1);

        return steering;
}
