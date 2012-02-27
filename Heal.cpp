#if PEKOMIN_GRAFO

#include "Mobile.hpp"
#include "Alien.hpp"
#include "Heal.hpp"

#define DEBUG_HEAL

#ifdef DEBUG_HEAL
#       include <iostream>
#endif

Heal::Heal(std::string name, Mobile *character, Mobile *target, double healTime, double healRadius) :
        Void(name),
        character(character),
        target(target),
        healTime(healTime),
        healRadius(healRadius),
        accum(0)
{}

void Heal::run(unsigned int ticks, unsigned int delta_ticks) {
        Alien *a;
        if (!(character)->active) {
                if((this->accum +=delta_ticks) >= healTime) {
                        character->active = true;
                        this->accum = 0;
                }
        }
        else {
                if ((target->pos - character->pos).length() < healRadius) {
                        if ((a = dynamic_cast<Alien *>(target)) != NULL) {
                                a->hp += 20;
                                if (a->hp > 100) a->hp = 100;
                                character->active = false;
                        }
                }
        }
}

#endif
