#include "KinematicSeek.hpp"

KinematicSeek::KinematicSeek(Ent character, Ent target, double maxSpeed) {
        character = character;
        target = target;
        maxSpeed = maxSpeed;
}

//esto devuelve velocidad y rotacion
pair<Triple,double> KinematicSeek::getSteering() {
        pair<Triple,double> steering;
        steering.first = target.pos - character.pos;
        steering.first.normalize();
        steering.first *= maxSpeed;
        character.ang = getNewOrientation(character.ang, steering.first);
        steering.second = 0;

        return steering;
}
