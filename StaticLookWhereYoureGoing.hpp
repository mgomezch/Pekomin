#ifndef STATICLOOKWHEREYOUREGOING_HPP
#define STATICLOOKWHEREYOUREGOING_HPP

#include "DirectStaticA.hpp"

using namespace std;

class Mobile;

class StaticLookWhereYoureGoing : public virtual DirectStaticA {
        public:
                Mobile *character;

                StaticLookWhereYoureGoing(string name, Mobile *character);

                virtual vector<double> getAng(unsigned int ticks);
};

#endif
