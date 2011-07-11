#ifndef _BEHAVIOR_HPP
#define _BEHAVIOR_HPP

#include <string>

using namespace std;

class Behavior {
        public:
                string name;
                bool active;

                Behavior(string name = "");

                virtual ~Behavior() = 0;
};

#endif
