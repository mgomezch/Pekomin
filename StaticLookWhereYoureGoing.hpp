#ifndef STATICLOOKWHEREYOUREGOING_HPP
#define STATICLOOKWHEREYOUREGOING_HPP

#include <vector>

#include "DirectStaticA.hpp"

class Mobile;

class StaticLookWhereYoureGoing : public virtual DirectStaticA {
        public:
                Mobile *character;

                StaticLookWhereYoureGoing(std::string name, Mobile *character);

                virtual std::vector<double> getAng(unsigned int ticks, unsigned int delta_ticks);
};

#endif
