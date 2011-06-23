#include <cmath>

#include "Align.hpp"
#include "Mobile.hpp"
#include "Triple.hpp"
#include "util.hpp"

//#define DEBUG_ALIGN

#ifdef DEBUG_ALIGN
#include <iostream>
#endif

Align::Align(Mobile *character, Mobile *target, double maxAngularVelocity, double targetRadius, double slowRadius) {
        this->character          = character         ;
        this->target             = target            ;
        this->maxAngularVelocity = maxAngularVelocity;
        this->targetRadius       = targetRadius      ;
        this->slowRadius         = slowRadius        ;
        this->dead               = false             ;
}

pair<bool, double> Align::getAngVel(unsigned int ticks) {
        pair<bool, double> steering;
        double rotation, rotationSize, targetRotation;
        Triple direction;

        steering.first = true;

        rotation = mapToRange(mapToRange(target->ang) - mapToRange(character->ang));
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
        if (rotationSize < slowRadius){
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

        //targetRotation *= map_atan(20000 * target->vrot);

        steering.second = targetRotation * (rotation > 0 ? -1 : 1);

        return steering;
}
