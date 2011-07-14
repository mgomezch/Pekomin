#include <string>

#include "Behavior.hpp"

Behavior::~Behavior() {}

Behavior::Behavior(string name):
        name(name),
        active(true),
        dead(false)
{}
