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
#include "Tabs.hpp"

#define PEKOMIN_DEBUG_TABS 1

#if PEKOMIN_DEBUG_TABS
#       include <iostream>
#endif

#define PEKOMIN_TABS_SEP 0.05

Tabs::Tabs(
        double                   p_width         ,
        double                   p_height        ,
        double                   p_header_height ,
        HUDCallback_t            p_raise_callback,
        HUDCallback_t            p_lower_callback,
        unsigned int             p_pages         ,
        GLubyte                  p_r             ,
        GLubyte                  p_g             ,
        GLubyte                  p_b             ,
        GLubyte                  p_a             ,
        Hideable                 p_hideable      ,
        HUDElement::Highlighting p_highlighting  ,
        HUDElement *             p_parent        ,
        std::string              p_name          ,
        HUDElement::Visibility   p_visible       ,
        Triple                   p_pos           ,
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
        width         (p_width         ),
        height        (p_height        ),
        header_height (p_header_height ),
        raise_callback(p_raise_callback),
        lower_callback(p_lower_callback),
        hideable      (p_hideable      ),
        active_page   (-1              )
{
        FilledWindow * h;
        FilledWindow * p;

        for (long int i = 0; i < static_cast<long int>(p_pages); ++i) {
                h = new FilledWindow(
                        (1 - PEKOMIN_TABS_SEP) * p_width / p_pages,
                        p_header_height,
                        p_r, p_g, p_b, p_a,
                        HUDElement::Highlighting::none,
                        this,
                        p_name + "->headers[" + std::to_string(i) + "]",
                        HUDElement::Visibility::visible
                );

                p = new FilledWindow(
                        p_width, p_height,
                        p_r, p_g, p_b, p_a,
                        HUDElement::Highlighting::none,
                        this,
                        p_name + "->pages[" + std::to_string(i) + "]",
                        HUDElement::Visibility::visible
                );

                h->set_callback_leftclick(
                        [this, i](HUDElement * self) {
                                if (lower_callback && active_page >= 0) lower_callback(this);

                                if (active_page != i) active_page = i;
                                else if (hideable == Hideable::yes) active_page = -1;

                                if (raise_callback && active_page >= 0) raise_callback(this);
                        }
                );

                headers.push_back(h);
                pages.push_back(p);
        }
}

void Tabs::draw(GLuint active_hud_elem) const {
        if (visible == HUDElement::Visibility::hidden) return;

        glPushMatrix();
                if (
                        highlighting == HUDElement::Highlighting::scale_wobble
                        && is(active_hud_elem)
                ) {
                        glScalef(
                                1 + PEKOMIN_HUD_HIGHLIGHT_SCALE * cos(PEKOMIN_HUD_HIGHLIGHT_SPEED * new_time) / width ,
                                1 + PEKOMIN_HUD_HIGHLIGHT_SCALE * cos(PEKOMIN_HUD_HIGHLIGHT_SPEED * new_time) / height,
                                1
                        );
                }

                if (active_page >= 0) {
                        glPushMatrix();
                                glTranslatef(
                                        pages[active_page]->pos.x,
                                        pages[active_page]->pos.y,
                                        pages[active_page]->pos.z
                                );
                                glRotatef(
                                        (pages[active_page]->ang * 180.0)/M_PI,
                                        0, 0, 1
                                );
                                pages[active_page]->draw(active_hud_elem);
                        glPopMatrix();
                }

                int n_pages = pages.size();
                double header_width = width/n_pages;
                for (int i = 0; i < n_pages; ++i) {
                        glPushMatrix();
                                glTranslatef(
                                        headers[i]->pos.x + ((2*i + 1)*header_width - width)/2.0,
                                        headers[i]->pos.y + (header_height + height)/2.0,
                                        headers[i]->pos.z
                                );
                                headers[i]->draw(active_hud_elem);
                        glPopMatrix();
                }
        glPopMatrix();
}

void Tabs::update() {
        std::for_each(headers.begin(), headers.end(), [](FilledWindow * w) { w->update(); });
        std::for_each(pages  .begin(), pages  .end(), [](FilledWindow * w) { w->update(); });
}

HUDElement * Tabs::contains(GLuint uid) const {
        HUDElement * p;

        for (auto it = headers.begin(); it != headers.end(); ++it) { if ((p = (*it)->contains(uid))) return p; }
        for (auto it = pages  .begin(); it != pages  .end(); ++it) { if ((p = (*it)->contains(uid))) return p; }

        return nullptr;
}
