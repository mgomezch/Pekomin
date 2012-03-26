#ifndef PEKOMIN_WINDOW_HPP
#define PEKOMIN_WINDOW_HPP

#include <GL/gl.h>
#include <list>
#include <string>

#include "HUDElement.hpp"
#include "Triple.hpp"

class Window : public virtual HUDElement {
        public:
                std::list<HUDElement *> children;

                Window(
                        HUDElement::Highlighting p_highlighting = HUDElement::Highlighting::none ,
                        HUDElement *             p_parent       = nullptr                        ,
                        std::string              p_name         = ""                             ,
                        HUDElement::Visibility   p_visible      = HUDElement::Visibility::visible,
                        Triple                   p_pos          = Triple()                       ,
                        double                   p_ang          = 0
                );

                virtual void draw(GLuint active_hud_elem) const;
                virtual void update(unsigned int ticks, unsigned int delta_ticks);

                virtual HUDElement * contains(GLuint uid) const;
};

#endif
