#ifndef WALLCLOSESTATEMACHINE_HPP
#define WALLCLOSESTATEMACHINE_HPP

#include <vector>

#include "DirectKinematicV.hpp"
#include "Triple.hpp"

class Mobile;
class Seek;

class WallCloseStateMachine : public virtual DirectKinematicV {
        public :
                enum class States : unsigned int {
                        SEEK,
                        FLEE
                };

                Mobile *character;
                Mobile *target;
                States state;
                Seek *seek_1, *seek_2;
                unsigned int last_ticks;

                WallCloseStateMachine(std::string name, Mobile *character, Mobile *target, double maxSpeed);

                virtual ~WallCloseStateMachine();

                virtual std::vector<Triple> getVel(unsigned int ticks, unsigned int delta_ticks);
};

#endif
