#include "KinematicArrive.hpp"
#include "Ent.hpp"

KinematicArrive::KinematicArrive(Ent *character_, Ent *target_, double maxSpeed_, double radius_) {
        character = character_;
        target    = target_;
        maxSpeed  = maxSpeed_;
        radius    = radius_;
}

pair<Triple, double> KinematicArrive::getSteering() {
        pair<Triple, double> steering;
        steering.first = target->pos - character->pos;

	//cuando no se cumple esto que se retorna? o que tiene el steering? o usar una referencia e instanciar a NULL y echarnos agua :D
	if (steering.first.length() >= radius) {
		steering.first /= timeToTarget;
//              steering.second = getNewOrientation(character->ang, steering.first);
        }

        return steering;
}
