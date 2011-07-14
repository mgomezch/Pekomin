#ifndef BEHAVIOR_HPP
#define BEHAVIOR_HPP

#include <string>

using namespace std;

class Behavior {
        public:
                string name;
                bool active;
                bool dead;

                Behavior(string name = "");

                virtual ~Behavior() = 0;
};

#endif
