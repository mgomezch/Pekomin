#include "KinematicArrive.hpp"
#include "Ent.hpp"

/*
unsigned int KinematicArrive::type() {
        return BEHAVIOR_KINEMATICARRIVE;
}
*/

KinematicArrive::KinematicArrive(Ent *character_, Ent *target_, double maxSpeed_, double radius_) {
        character = character_;
        target    = target_;
        maxSpeed  = maxSpeed_;
        radius    = radius_;
}

tuple<bool, Triple, double> KinematicArrive::getVel() {
        tuple<bool, Triple, double> steering;

	get<0>(steering) = false;
        get<2>(steering) = 0;

	get<1>(steering) = target->pos - character->pos;

        if (get<1>(steering).length() > radius) {
		get<0>(steering) = true;
		get<1>(steering) /= timeToTarget;
		if (get<1>(steering).length() > maxSpeed) {
			get<1>(steering).normalized();
			get<1>(steering) *= maxSpeed;
		}
        }

        return steering;
}
