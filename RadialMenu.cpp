#include <algorithm>
#include <cmath>
#include <GL/gl.h>
#include <string>

#include "events.hpp"
#include "game.hpp"
#include "gl.hpp"
#include "Triple.hpp"
#include "util.hpp"

#include "HUDElement.hpp"
#include "FilledWindow.hpp"
#include "RadialMenu.hpp"

#define PEKOMIN_DEBUG_TABS 1

#if PEKOMIN_DEBUG_TABS
#       include <iostream>
#endif

RadialMenu::RadialMenu(
        HUDElement *             p_controller   ,
        double                   p_radius       ,
        double                   p_angle_start  ,
        double                   p_angle_end    ,
        double                   p_speed        ,
        bool                     p_active       ,
        Alignment                p_alignment    ,
        HUDCallback_t            p_show_callback,
        HUDCallback_t            p_hide_callback,
        Hideable                 p_hideable     ,
        HUDElement::Highlighting p_highlighting ,
        HUDElement *             p_parent       ,
        std::string              p_name         ,
        HUDElement::Visibility   p_visible      ,
        Triple                   p_pos          ,
        double                   p_ang
):
        HUDElement(
                p_highlighting,
                p_parent      ,
                p_name        ,
                p_visible     ,
                p_pos         ,
                p_ang
        ),
        controller    (p_controller           ),
        radius        (p_radius               ),
        angle_start   (p_angle_start          ),
        angle_end     (p_angle_end            ),
        speed         (p_speed                ),
        active        (p_active               ),
        alignment     (p_alignment            ),
        show_callback (p_show_callback        ),
        hide_callback (p_hide_callback        ),
        hideable      (p_hideable             ),
        current_radius(p_active ? p_radius : 0),
        radius_t      (p_active ? 1        : 0)
{
        controller->set_callback_leftclick(
                [this](HUDElement * self) {
                        if (hideable == RadialMenu::Hideable::yes) {
                                if (active) { if (hide_callback) hide_callback(this); active = false; }
                                else        { if (show_callback) show_callback(this); active = true ; }
                        }
                }
        );
}

void RadialMenu::draw(GLuint active_hud_elem) const {
        if (visible == HUDElement::Visibility::hidden) return;

        glPushMatrix();
                glPushMatrix();
                        glTranslatef(
                                controller->pos.x,
                                controller->pos.y,
                                controller->pos.z
                        );
                        glRotatef(
                                (controller->ang * 180.0)/M_PI,
                                0, 0, 1
                        );
                        controller->draw(active_hud_elem);
                glPopMatrix();

                if (radius_t != 0 && !children.empty()) {
                        double ang_incr;
                        double ang = angle_start;

                        if (children.size() != 1) {
                                if (angle_start == angle_end) ang_incr = 360;
                                else ang_incr = angle_start - angle_end;
                                ang_incr /= children.size() - 1;
                        } else if (angle_start != angle_end) ang = (angle_start + angle_end)/2;

                        glPushMatrix();
                                std::for_each(
                                        children.begin(),
                                        children.end(),
                                        [&](decltype(*children.begin()) c) {
                                                glPushMatrix();
                                                        glRotatef(ang*radius_t, 0, 0, -1);
                                                        glTranslatef(current_radius, 0, 0);
                                                        glTranslatef(
                                                                c->pos.x,
                                                                c->pos.y,
                                                                c->pos.z
                                                        );
                                                        glRotatef(
                                                                (controller->ang * 180.0)/M_PI,
                                                                0, 0, 1
                                                        );
                                                        switch (alignment) {
                                                                case RadialMenu::Alignment::horizontal: glRotatef(-ang, 0, 0, -1); break;
                                                                case RadialMenu::Alignment::tangential: glRotatef(- 90, 0, 0, -1); break;
                                                        }
                                                        glScalef(radius_t, radius_t, radius_t);
                                                        c->draw(active_hud_elem);
                                                glPopMatrix();
                                                ang += ang_incr;
                                        }
                                );
                        glPopMatrix();
                }
        glPopMatrix();
}

void RadialMenu::update(unsigned int ticks, unsigned int delta_ticks) {
        HUDElement::update(ticks, delta_ticks);

        radius_t += (active ? 1.0 : -1.0) * static_cast<double>(speed*delta_ticks);
        if (radius_t < 0) radius_t = 0;
        if (radius_t > 1) radius_t = 1;
        current_radius = radius * radius_t*radius_t * (radius_t - 2)*(radius_t - 2);

        if (radius_t) {
                controller->update(ticks, delta_ticks);
                std::for_each(
                        children.begin(),
                        children.end(),
                        [ticks, delta_ticks](HUDElement * e) {
                                e->update(ticks, delta_ticks);
                        }
                );
        }
}

HUDElement * RadialMenu::contains(GLuint uid) const {
        HUDElement * p;

        if ((p = controller->contains(uid))) return p;

        for (auto it = children.begin(); it != children.end(); ++it) {
                if ((p = (*it)->contains(uid))) return p;
        }

        return nullptr;
}
