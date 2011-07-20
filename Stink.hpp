#ifndef STINK_HPP
#define STINK_HPP

#include "Void.hpp"

class Mobile;

class Stink : public virtual Void {
        public:
                Mobile *character;
                unsigned int stinkTime;
                unsigned int lifetime;
                double intensity;
                double spread;

                Stink(std::string name, Mobile *character, unsigned int stinkTime, unsigned int lifetime, double intensity, double spread);

                virtual void run(unsigned int ticks, unsigned int delta_ticks);

        private:
                unsigned int accum;
};

#endif
