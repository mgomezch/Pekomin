#include <GL/gl.h>

#include "HUDElement.hpp"
#include "Triple.hpp"

#define PEKOMIN_DEBUG_HUDELEMENT

#ifdef PEKOMIN_DEBUG_HUDELEMENT
#       include <iostream>
#endif

GLuint next_select_uid = 1;

HUDElement::HUDElement(
        HUDElement::Highlighting p_highlighting,
        HUDElement *             p_parent      ,
        std::string              p_name        ,
        HUDElement::Visibility   p_visible     ,
        Triple                   p_pos         ,
        double                   p_ang
):
        highlighting (p_highlighting),
        parent       (p_parent      ),
        name         (p_name        ),
        visible      (p_visible     ),
        pos          (p_pos         ),
        ang          (p_ang         ),

//      dead         (false         ),
        new_pos      (p_pos         ),
        new_ang      (p_ang         ),

#define PEKOMIN_INITIALIZE_CALLBACK_MEMBER(event) callback_##event(nullptr),
        PEKOMIN_EVENTS(PEKOMIN_INITIALIZE_CALLBACK_MEMBER)
#undef PEKOMIN_INITIALIZE_CALLBACK_MEMBER

        select_uid(next_select_uid++)
{}

HUDElement::~HUDElement() {}

void HUDElement::update() {
        this->new_pos = this->pos;
        this->new_ang = this->ang;
}

#define PEKOMIN_DEFINE_CALLBACK_SETTER(event)                             \
        HUDElement & HUDElement::set_callback_##event(HUDCallback_t cb) { \
                callback_##event = cb;                                    \
                return *this;                                             \
        }
PEKOMIN_EVENTS(PEKOMIN_DEFINE_CALLBACK_SETTER)
#undef PEKOMIN_DEFINE_CALLBACK_SETTER

HUDElement * HUDElement::is(GLuint uid) const {
        return uid == select_uid ? const_cast<HUDElement *>(this) : nullptr;
}

HUDElement * HUDElement::contains(GLuint uid) const {
        return is(uid);
}
