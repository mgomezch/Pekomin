#ifndef PEKOMIN_EVENTS_H
#define PEKOMIN_EVENTS_H

#define PEKOMIN_CLICK_EVENTS(EVENT) \
        EVENT(leftclick  )          \
        EVENT(middleclick)          \
        EVENT(rightclick )          \

#define PEKOMIN_KEY_EVENTS(EVENT) \
        EVENT(key_l)              \
        EVENT(key_r)              \
        EVENT(key_u)              \
        EVENT(key_d)              \

#define PEKOMIN_EVENTS(EVENT)       \
        PEKOMIN_CLICK_EVENTS(EVENT) \
        PEKOMIN_KEY_EVENTS(EVENT)   \

#endif
