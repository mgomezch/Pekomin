#include <cmath>
#include <GL/gl.h>

#include "HUDElement.hpp"
#include "Triple.hpp"

#define PEKOMIN_DEBUG_HUDELEMENT

#ifdef PEKOMIN_DEBUG_HUDELEMENT
#       include <iostream>
#endif

GLuint next_select_uid = 1;

HUDElement::HUDElement(
        std::string name,
        Triple pos,
        double ang,
        bool visible
):
        name(name),
        pos(pos),
        ang(ang),
//      dead(false),
        new_pos(pos),
        new_ang(ang),
        leftclick(leftclick),
        middleclick(middleclick),
        rightclick(rightclick),
        visible(visible),
        select_uid(next_select_uid++)
{}

HUDElement::~HUDElement() {}

void HUDElement::update() {
        this->new_pos = this->pos;
        this->new_ang = this->ang;
}

const Triple HUDElement::orientation() const {
        return Triple(cos(ang), sin(ang), 0);
}

void HUDElement::set_leftclick  (std::function<void(HUDElement *)> callback) { leftclick   = callback; }
void HUDElement::set_middleclick(std::function<void(HUDElement *)> callback) { middleclick = callback; }
void HUDElement::set_rightclick (std::function<void(HUDElement *)> callback) { rightclick  = callback; }

bool HUDElement::identify(GLuint uid) {
        return uid == select_uid;
}
