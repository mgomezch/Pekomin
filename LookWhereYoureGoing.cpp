#include "LookWhereYoureGoing.hpp"	

LookWhereYoureGoing(Mobile *character, Mobile *target, double maxAngularAcceleration, double maxRotation, double targetRadius, double slowRadius) : Align(character, target, maxAngularAcceleration, maxRotation, targetRadius, slowRadius) {}

tuple <bool, Triple, double> LookWhereYoureGoing::getVelInc() {

	if (character.vel.length() > 0)
		target->ang = atan2(-character->vel.x, character->vel.y);

	return Align::getVelInc();

}
