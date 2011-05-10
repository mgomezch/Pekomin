#include "KinematicFlee.hpp"

KinematicFlee::KinematicFlee(Ent character, Ent target, double maxSpeed) {
        character = character;
        target    = target;
        maxSpeed  = maxSpeed;
}

//esto devuelve velocidad y rotacion
pair<Triple,double> KinematicFlee::getSteering() {
        pair<Triple,double> steering;
        steering.first = character.pos - target.pos;
        steering.first.normalize();
        steering.first *= maxSpeed;
        character.ang = getNewOrientation(character.ang, steering.first);
        steering.second = 0;

        return steering;
}
