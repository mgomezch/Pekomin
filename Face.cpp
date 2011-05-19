#include <cmath>

#include "Face.hpp"
#include "Mobile.hpp"
#include "util.hpp"

//#define DEBUG_FACE

#ifdef DEBUG_FACE
#include <iostream>
#endif

Face::Face(Mobile *character, Mobile *target, double maxAngularVelocity, double targetRadius, double slowRadius) {
        this->character          = character;
        this->target             = target;
        this->maxAngularVelocity = maxAngularVelocity;
        this->targetRadius       = targetRadius;
        this->slowRadius         = slowRadius;
}

tuple<bool, Triple, double> Face::getVelIncr(unsigned int ticks) {
        tuple<bool, Triple, double> steering;
        double rotation, rotationSize, targetRotation;
        Triple direction;

        get<0>(steering) = true;
        get<1>(steering) = 0;

        direction = target->pos - character->pos;
        rotation = atan2(direction.y, direction.x) - mapToRange(character->ang);
        if (rotation > M_PI) rotation -= 2 * M_PI;
        rotationSize = abs(rotation);

        if (rotationSize < targetRadius) {
#ifdef DEBUG_FACE
                cout << "Face " << static_cast<void *>(this) << ": dentro de targetRadius" << endl;
#endif
                get<2>(steering) = target->vrot - character->vrot;
                if (abs(get<2>(steering)) > maxAngularVelocity) {
                        get<2>(steering) = maxAngularVelocity;
                }
                return steering;
        }

        targetRotation = maxAngularVelocity;// - target->vrot;
        if (rotationSize < slowRadius) {
#ifdef DEBUG_FACE
                cout << "Face " << static_cast<void *>(this) << ": entre targetRadius y slowRadius" << endl;
#endif
                targetRotation *= rotationSize / slowRadius;
        }
#ifdef DEBUG_FACE
        else {
                cout << "Face " << static_cast<void *>(this) << ": fuera de slowRadius" << endl;
        }
#endif
        if (targetRotation < 0) targetRotation = 0;

        get<2>(steering) = targetRotation * (rotation > 0 ? 1 : -1);

        return steering;
}
