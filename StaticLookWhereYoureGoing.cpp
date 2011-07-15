#include "StaticLookWhereYoureGoing.hpp"
#include "Mobile.hpp"
#include "util.hpp"

StaticLookWhereYoureGoing::StaticLookWhereYoureGoing(string name, Mobile *character):
        DirectStaticA(name),
        character(character)
{}

pair<bool, double> StaticLookWhereYoureGoing::getAng(unsigned int ticks) {
        pair<bool, double> steering;

        if (character->vel.x == 0 && character->vel.y == 0) steering.first = false;
        else {
                steering.first  = true;
                steering.second = character->vel.ang_xy();
        }

        return steering;
}
