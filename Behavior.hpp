#ifndef BEHAVIOR_HPP
#define BEHAVIOR_HPP

#include <string>

class Behavior {
        public:
                std::string name;
                bool active;
                bool dead;

                Behavior(std::string name = "");

                virtual ~Behavior() = 0;
};

#endif
