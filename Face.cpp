#include <cmath>

#include "Face.hpp"
#include "Mobile.hpp"
#include "util.hpp"

//#define DEBUG_FACE

#ifdef DEBUG_FACE
#include <iostream>
#endif

Face::Face(Mobile *character, Mobile *target, double maxAngularVelocity, double targetRadius, double slowRadius) {
        this->character          = character         ;
        this->target             = target            ;
        this->maxAngularVelocity = maxAngularVelocity;
        this->targetRadius       = targetRadius      ;
        this->slowRadius         = slowRadius        ;
        this->dead               = false             ;
}

pair<bool, double> Face::getAngVelIncr(unsigned int ticks) {
        pair<bool, double> steering;
        double rotation, rotationSize, targetRotation;
        Triple direction;
        Triple cp, tp;

        steering.first = true;

        tie(cp, tp) = points(this->character, this->target);
        direction = tp - cp;
        rotation = mapToRange(atan2(direction.y, direction.x) - character->ang);
        //if (rotation > M_PI) rotation -= 2 * M_PI;
        rotationSize = abs(rotation);

        if (rotationSize < targetRadius) {
#ifdef DEBUG_FACE
                cout << "Face " << static_cast<void *>(this) << ": dentro de targetRadius" << endl;
#endif
                steering.second = target->vrot - character->vrot;
                if (abs(steering.second) > maxAngularVelocity) {
                        steering.second = maxAngularVelocity;
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
        //if (targetRotation < 0) targetRotation = 0;

        steering.second = targetRotation * (rotation > 0 ? -1 : 1);

        return steering;
}
