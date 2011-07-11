#ifndef _STATEMACHINE_HPP
#define _STATEMACHINE_HPP

#define WANDER        (1 << 0) /* 0x01 */
#define SEEK          (1 << 1) /* 0x02 */
#define FLEE          (1 << 2) /* 0x04 */
#define ARRIVE        (1 << 3) /* 0x08 */
#define PURSUE        (1 << 4) /* 0x10 */
#define EVADE         (1 << 5) /* 0x20 */
#define PATHFOLLOWING (1 << 6) /* 0x40 */
#define NADA          (1 << 7) /* 0x80 */

class StateMachine {
        public:
                unsigned int states; //: 8;

                StateMachine();
                void active_behavior(unsigned int behavior);
                void desactive_behavior(unsigned int behavior);
                unsigned int get_behavior(unsigned int behavior);

                void state_to_bynary(unsigned int behavior);

};

#endif
