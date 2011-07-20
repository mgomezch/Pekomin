#ifndef VOID_HPP
#define VOID_HPP

#include <string>

#include "Behavior.hpp"

class Void : public virtual Behavior {
        public:
                Void(std::string name);

                virtual void run(unsigned int ticks, unsigned int delta_ticks) = 0;
};

#endif
