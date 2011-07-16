#include <cmath>
#include <vector>

#include "Face.hpp"
#include "Mobile.hpp"
#include "Triple.hpp"
#include "util.hpp"

//#define DEBUG_FACE

#ifdef DEBUG_FACE
#include <iostream>
#endif

Face::Face(string name, Mobile *character, Mobile *target, double maxAngularVelocity, double targetRadius, double slowRadius):
        KinematicA(name),
        character(character),
        target(target),
        maxAngularVelocity(maxAngularVelocity),
        targetRadius(targetRadius),
        slowRadius(slowRadius)
{}

vector<double> Face::getAngVelIncr(unsigned int ticks) {
        double steering;
        double rotation, rotationSize, targetRotation;
        Triple direction;
        Triple cp, tp;

        tie(cp, tp) = points(this->character, this->target);
        direction = tp - cp;
        rotation = mapToRange(atan2(direction.y, direction.x) - character->ang);
        //if (rotation > M_PI) rotation -= 2 * M_PI;
        rotationSize = abs(rotation);

        if (rotationSize < targetRadius) {
#ifdef DEBUG_FACE
                cout << "Face " << static_cast<void *>(this) << ": dentro de targetRadius" << endl;
#endif
                steering = target->vrot - character->vrot;
                if (abs(steering) > maxAngularVelocity) {
                        steering = maxAngularVelocity;
                }
                return vector<double>(1, steering);
        }

        targetRotation = maxAngularVelocity; // - target->vrot;
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

        steering = targetRotation * (rotation > 0 ? -1 : 1);

        return vector<double>(1, steering);
}
