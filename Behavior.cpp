#include <string>

#include "Behavior.hpp"

Behavior::~Behavior() {}

Behavior::Behavior(std::string name):
        name(name),
        active(true),
        dead(false)
{}
