#include "KinematicFlee.hpp"

KinematicFlee::KinematicFlee(Ent *character_, Ent *target_, double maxSpeed_) {
        character = character_;
        target    = target_;
        maxSpeed  = maxSpeed_;
}

// Retorna incrementos de velocidad y rotación
pair<Triple, double> KinematicFlee::getSteering() {
        pair<Triple, double> steering;
        steering.first = character->pos - target->pos;
        steering.first.normalize();
        steering.first *= maxSpeed;
        character->ang = getNewOrientation(character->ang, steering.first);
        steering.second = 0;

        return steering;
}

string KinematicFlee::name() {
	return "KinematicFlee";
}
