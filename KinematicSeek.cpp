#include "KinematicSeek.hpp"

KinematicSeek::KinematicSeek(Ent *character_, Ent *target_, double maxSpeed_) {
        character = character_;
        target    = target_;
        maxSpeed  = maxSpeed_;
}

// Retorna incrementos de velocidad y rotacion
pair<Triple,double> KinematicSeek::getSteering() {
        pair<Triple, double> steering;
        steering.first = target->pos - character->pos;
        steering.first.normalize();
        steering.first *= maxSpeed;
        character->ang = getNewOrientation(character->ang, steering.first);
        steering.second = 0;

        return steering;
}

string KinematicSeek::name() {
	return "KinematicSeek";
}
