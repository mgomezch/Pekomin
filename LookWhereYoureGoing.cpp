#include <cmath>

#include "LookWhereYoureGoing.hpp"
#include "Mobile.hpp"

LookWhereYoureGoing::LookWhereYoureGoing(Mobile *character, Mobile *target, double maxAngularAcceleration, double maxRotation, double targetRadius, double slowRadius) {
        this->character              = character;
        this->target                 = target;
        this->maxAngularAcceleration = maxAngularAcceleration;
        this->maxRotation            = maxRotation;
        this->targetRadius           = targetRadius;
        this->slowRadius             = slowRadius;
}

tuple<bool, Triple, double> LookWhereYoureGoing::getVelIncr(unsigned int ticks) {
        tuple<bool, Triple, double> steering;
        double rotation, rotationSize, targetRotation, angularAcceleration;

        if (character->vel.length() == 0) {
                get<0>(steering) = false;
                return steering;
        }

        rotation = atan2(-character->vel.y, character->vel.x) - character->ang;
        mapToRange(&rotation);
        rotationSize = abs(rotation);

        if (rotationSize < targetRadius) {
                get<0>(steering) = true;
                return steering;
        }

        if (rotationSize > slowRadius) {
                targetRotation = maxRotation;
        }
        else {
                targetRotation = maxRotation * rotationSize / slowRadius;
        }

        targetRotation *= rotation / rotationSize;
        get<2>(steering) = targetRotation - character->ang;
        get<2>(steering) /= timeToTarget;
        angularAcceleration = abs(get<2>(steering));

        if (angularAcceleration > maxAngularAcceleration) {
                get<2>(steering) /= angularAcceleration;
                get<2>(steering) *= maxAngularAcceleration;
        }

        get<0>(steering) = true;
        get<1>(steering) = 0;

        return steering;
}

void LookWhereYoureGoing::mapToRange(double *value) {
        if (*value > M_PI) {
                *value -= 2 * M_PI;
                mapToRange(value);
        }

        else if(*value < -M_PI) {
                *value += 2 * M_PI;
                mapToRange(value);
        }
}
