#include <cmath>

#include "LookWhereYoureGoing.hpp"
#include "Mobile.hpp"
#include "util.hpp"

//#define DEBUG_LOOKWHEREYOUREGOING

#ifdef DEBUG_LOOKWHEREYOUREGOING
#include <iostream>
#endif

LookWhereYoureGoing::LookWhereYoureGoing(Mobile *character, double maxAngularVelocity, double targetRadius, double slowRadius) {
        this->character          = character;
        this->maxAngularVelocity = maxAngularVelocity;
        this->targetRadius       = targetRadius;
        this->slowRadius         = slowRadius;
}

tuple<bool, Triple, double> LookWhereYoureGoing::getVelIncr(unsigned int ticks) {
        tuple<bool, Triple, double> steering;
        double rotation, rotationSize, targetRotation;
        Triple direction;

        get<0>(steering) = true;
        get<1>(steering) = 0;

        direction = character->vel;
        if (direction.length() == 0) {
                get<0>(steering) = false;
                return steering;
        }
        rotation = mapToRange(atan2(direction.y, direction.x)) - mapToRange(character->ang);
        if (rotation > M_PI) rotation -= 2 * M_PI;
        rotationSize = abs(rotation);

        if (rotationSize < targetRadius) {
#ifdef DEBUG_LOOKWHEREYOUREGOING
                cout << "LookWhereYoureGoing " << static_cast<void *>(this) << ": dentro de targetRadius" << endl;
#endif
                get<2>(steering) = -character->vrot;
                if (abs(get<2>(steering)) > maxAngularVelocity) {
                        get<2>(steering) = maxAngularVelocity;
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
        if (targetRotation < 0) targetRotation = 0;

        get<2>(steering) = targetRotation * (rotation > 0 ? 1 : -1);

        return steering;
}

