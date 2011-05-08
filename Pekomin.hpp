#ifndef _PEKOMIN_HPP
#define _PEKOMIN_HPP

#include "Mobile.hpp"

using namespace std;

class Pekomin : Mobile {
        public:
                unsigned int state;
                vector<Behavior *> behaviors;
};

#endif
