#include <algorithm>
#include <cmath>
#include <GL/gl.h>
#include <string>

#include "game.hpp"
#include "gl.hpp"
#include "HUDElement.hpp"
#include "Triple.hpp"
#include "Window.hpp"

Window::Window(
        HUDElement::Highlighting p_highlighting,
        HUDElement *             p_parent      ,
        std::string              p_name        ,
        HUDElement::Visibility   p_visible     ,
        Triple                   p_pos         ,
        double                   p_ang
):
        HUDElement(
                p_highlighting,
                p_parent      ,
                p_name        ,
                p_visible     ,
                p_pos         ,
                p_ang
        )
{}

void Window::draw(GLuint active_hud_elem) const {
        if (visible == HUDElement::Visibility::hidden) return;

        glPushMatrix();
                std::for_each(
                        children.begin(),
                        children.end(),
                        [active_hud_elem](HUDElement * c) {
                                glPushMatrix();
                                        glTranslatef(
                                                c->pos.x,
                                                c->pos.y,
                                                c->pos.z
                                        );
                                        glRotatef(
                                                (c->ang * 180.0)/M_PI,
                                                0, 0, 1
                                        );
                                        c->draw(active_hud_elem);
                                glPopMatrix();
                        }
                );
        glPopMatrix();
}

void Window::update() {
        std::for_each(
                children.begin(),
                children.end(),
                [](HUDElement * c) {
                        c->update();
                }
        );
}

HUDElement * Window::contains(GLuint uid) const {
        HUDElement * p;

        if ((p = HUDElement::contains(uid))) return p;

        for (auto it = children.begin(); it != children.end(); ++it) {
                if ((p = (*it)->contains(uid))) return p;
        }

        return nullptr;
}
