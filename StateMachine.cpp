#include "StateMachine.hpp"

#include <stdio.h>

StateMachine::StateMachine() {}

void StateMachine::active_behavior(unsigned int behavior) {
        states |= behavior;
}

void StateMachine::desactive_behavior(unsigned int behavior) {
        states &= ~behavior;
}

unsigned int StateMachine::get_behavior(unsigned int behavior) {
        return (states & behavior) != 0;
}

void StateMachine::state_to_bynary(unsigned int behavior) {
        unsigned int i, mask = 1 << 31;

        for (i = 0; i < 32; i++) {
                putchar(((behavior & mask) == 0) ? '0' : '1');
                behavior << 1;
                if (i % 8 == 0 && i != 32) putchar(' ');
                if (i == 31) putchar('\n');
        }
}
