#include <vector>

#include "StaticLookWhereYoureGoing.hpp"
#include "Mobile.hpp"
#include "util.hpp"

StaticLookWhereYoureGoing::StaticLookWhereYoureGoing(string name, Mobile *character):
        DirectStaticA(name),
        character(character)
{}

vector<double> StaticLookWhereYoureGoing::getAng(unsigned int ticks) {
        if (character->vel.x == 0 && character->vel.y == 0) return vector<double>();
        return vector<double>(1, character->vel.ang_xy());
}
