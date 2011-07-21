#ifndef HEAL_HPP
#define HEAL_HPP

#include "Void.hpp"

class Mobile;

class Heal : public virtual Void {
        public :
                Mobile *character;
                Mobile *target;
                double healTime;
                double healRadius;

                Heal(std::string name, Mobile *character, Mobile *targer, double healTime, double healRadius);

                virtual void run(unsigned int ticks, unsigned int delta_ticks);

        private:
                unsigned int accum;
};

#endif
