#include "Face.hpp"
#include "Mobile.hpp"

Face::Face(Mobile *character, Mobile *target, double maxAngularAcceleration, double maxRotation, double targetRadius, double slowRadius) {
        this->character              = character;
        this->target                 = target;
        this->maxAngularAcceleration = maxAngularAcceleration;
        this->maxRotation            = maxRotation;
        this->targetRadius           = targetRadius;
        this->slowRadius             = slowRadius;
}

tuple<bool, Triple, double> Face::getVelIncr() {
        tuple<bool, Triple, double> steering;
        double rotation, rotationSize, targetRotation, angularAcceleration;
        Triple direction;

        direction = target->pos - character->pos;

        rotation = atan2(-direction.x, direction.y); - character->ang;
        mapToRange(&rotation);
        rotationSize = abs(rotation);

        if (rotationSize >= targetRadius) {
                if (rotationSize > slowRadius) targetRotation = maxRotation;
                else                           targetRotation = maxRotation * rotationSize / slowRadius;

                targetRotation *= rotation / rotationSize;
                get<2>(steering) = targetRotation - character->ang;
                get<2>(steering) /= timeToTarget;
                angularAcceleration = abs(get<2>(steering));

                if (angularAcceleration > maxAngularAcceleration) {
                        get<2>(steering) /= angularAcceleration;
                        get<2>(steering) *= maxAngularAcceleration;
                }

                get<1>(steering) = 0;
        }

        return steering;
}

void Face::mapToRange(double *value) {
        if (*value > M_PI) {
                *value -= 2 * M_PI;
                mapToRange(value);
        }

        else if(*value < -M_PI) {
                *value += 2 * M_PI;
                mapToRange(value);
        }
}
