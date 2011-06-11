#ifndef _LINE_HPP
#define _LINE_HPP

#include "Mobile.hpp"

using namespace std;

class Line : public Mobile {
        public:
                Triple p1, p2;

                Triple v1();
                Triple v2();
};

#endif
