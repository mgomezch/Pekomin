#include "Kinematic.hpp"

void Kinematic::update(pair<Triple,double> steering, double time) {
        position    += velocity        * time;
        orientation += rotation        * time;
        velocity    += steering.first  * time;
        orientation += steering.second * time;
}

double Kinematic::getNewOrientation(double currentOrientation, Triple velocity) {
        if (velocity.length() > 0) {
                return atan2(-position.x,position.z);
        } else {
                return currentOrientation;
        }
}
