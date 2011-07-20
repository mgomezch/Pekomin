#include <algorithm>
#include <vector>

#include "game.hpp"
#include "Mobile.hpp"
#include "Smell.hpp"
#include "Triple.hpp"

#define DEBUG_SMELL

#ifdef DEBUG_SMELL
#       include <iostream>
#       define DEBUG_SMELL_PRINT(S) std::cout << "DEBUG: Smell " << reinterpret_cast<void *>(this) << ": " #S << " == " << S << std::endl;
#else
#       define DEBUG_SMELL_PRINT(S)
#endif

Smell::Smell(std::string name, Mobile *character, double maxSpeed, double range):
        DirectKinematicV(name),
        character(character),
        maxSpeed(maxSpeed),
        range(range)
{}

std::vector<Triple> Smell::getVel(unsigned int ticks, unsigned int delta_ticks) {
        Triple steering, dir;
        Triple cp, tp;
        double d, x, f;

        if (odors.empty()) return std::vector<Triple>();

        for (auto it = odors.begin(); it != odors.end(); ++it) {
                std::tie(cp, tp) = points(this->character, *it);
                dir = cp - tp;
                d = dir.length();
                if (d > this->range) continue;
                x = d/(1 + ((*it)->spread * static_cast<double>((*it)->accum))/static_cast<double>((*it)->lifetime));
                f = (*it)->intensity * std::exp(-x*x/100.0);
                DEBUG_SMELL_PRINT(x)
                DEBUG_SMELL_PRINT(f)
                steering -= (dir * maxSpeed * f)/d;
        }

        return std::vector<Triple>(1, steering);
}
