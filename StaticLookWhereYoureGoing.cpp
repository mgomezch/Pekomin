#include <vector>

#include "StaticLookWhereYoureGoing.hpp"
#include "Mobile.hpp"
#include "util.hpp"

StaticLookWhereYoureGoing::StaticLookWhereYoureGoing(std::string name, Mobile *character):
        DirectStaticA(name),
        character(character)
{}

std::vector<double> StaticLookWhereYoureGoing::getAng(unsigned int ticks, unsigned int delta_ticks) {
        if (character->vel.x == 0 && character->vel.y == 0) return std::vector<double>();
        return std::vector<double>(1, character->vel.ang_xy());
}
