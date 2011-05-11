#include "Seek.hpp"
#include "Mobile.hpp"

Seek::Seek(Mobile *character, Mobile *target, double maxAcceleration) {
	this->character       = character;
	this->target          = target;
	this->maxAcceleration = maxAcceleration;
}

pair<Triple, double> Seek::getSteering() {
	pair<Triple, double> steering;

	steering.first = target->pos - character->pos;
	steering.first.normalize();
	steering.first *= maxAcceleration;
	steering.second = 0;

	return steering;
}
