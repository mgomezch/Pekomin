#include "Mobile.hpp"
#include "WallCloseStateMachine.hpp"
#include "Triple.hpp"

#include "Seek.hpp"

#define DEBUG_WALLCLOSESTATEMACHINE

#ifdef DEBUG_WALLCLOSESTATEMACHINE
#       include <iostream>
#endif

WallCloseStateMachine::WallCloseStateMachine(std::string name, Mobile *character, Mobile *target, double maxSpeed):
        DirectKinematicV(name),
        character(character),
        target(target),
        state(States::SEEK),
        seek_1(new Seek(name + "Seek_1", character, target, maxSpeed)),
        seek_2(new Seek(name + "Seek_2", character, target, -maxSpeed)),
        last_ticks(0)
{
        this->seek_2->active = false;
}

WallCloseStateMachine::~WallCloseStateMachine() {
        delete this->seek_2;
        delete this->seek_1;
}

std::vector<Triple> WallCloseStateMachine::getVel(unsigned int ticks, unsigned int delta_ticks) {
        Triple cp, tp;
        double distance;
        std::vector<Triple> temp;
        std::vector<Triple> out;
        int go = 0;

        if (this->last_ticks != ticks) {
                this->last_ticks = ticks;
                std::tie(cp, tp) = points(character, target);
                distance = (tp - cp).length();

                if (state != States::SEEK && distance > 80) {
                        this->state = States::SEEK;
                        this->seek_1->active = true ;
                        this->seek_2->active = false;
                        go = 0;
                }
                else if (state != States::FLEE && distance <= 5 && go == 0) {
                        this->state = States::FLEE;
                        this->seek_1->active = false;
                        this->seek_2->active = true ;
                        go = 1;
                }
        }

        if (this->seek_1->active) {
                temp = seek_1->getVel(ticks, delta_ticks);
                out.insert(out.begin(), temp.begin(), temp.end());
        }
        if (this->seek_2->active) {
                temp = seek_2->getVel(ticks, delta_ticks);
                out.insert(out.begin(), temp.begin(), temp.end());
        }

        return out;
}
