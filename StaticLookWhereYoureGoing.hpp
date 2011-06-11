#ifndef _STATICLOOKWHEREYOUREGOING_HPP
#define _STATICLOOKWHEREYOUREGOING_HPP

#include "DirectStaticA.hpp"

using namespace std;

class Mobile;

class StaticLookWhereYoureGoing : public DirectStaticA {
        public:
                Mobile *character;

                StaticLookWhereYoureGoing(Mobile *character);

                virtual pair<bool, double> getAng(unsigned int ticks);
};

#endif
