#include <string>
#include <sstream>

#include "game.hpp"
#include "Mobile.hpp"
#include "Odor.hpp"
#include "Stink.hpp"

//#define DEBUG_STINK

#ifdef DEBUG_STINK
#       include <iostream>
#       define DEBUG_STINK_PRINT(S) std::cout << "DEBUG: Stink " << reinterpret_cast<void *>(this) << ": " #S << " == " << S << std::endl;
#else
#       define DEBUG_STINK_PRINT(S)
#endif

Stink::Stink(std::string name, Mobile *character, unsigned int stinkTime, unsigned int lifetime, double intensity, double spread):
        Void(name),
        character(character),
        stinkTime(stinkTime),
        lifetime(lifetime),
        intensity(intensity),
        spread(spread),
        accum(0)
{}

void Stink::run(unsigned int ticks, unsigned int delta_ticks) {
        //DEBUG_STINK_PRINT(accum);
        if ((this->accum += delta_ticks) >= stinkTime) {
                std::stringstream name;
                name << this->name << " " << ticks;
                DEBUG_STINK_PRINT(true);
                Odor *odor = new Odor(name.str(), this->character->pos, this->lifetime, this->intensity, this->spread);
                new_odors.push_back(odor);
                new_ents.push_back(odor);
                this->accum = 0;
        }
        //DEBUG_STINK_PRINT(false);
}
