#include <cmath>
#include <GL/gl.h>
#include <string>

#include "events.hpp"
#include "game.hpp"
#include "gl.hpp"
#include "Triple.hpp"
#include "util.hpp"

#include "HUDElement.hpp"
#include "Window.hpp"
#include "FilledWindow.hpp"
#include "Tab.hpp"

#define PEKOMIN_DEBUG_TAB 1

#if PEKOMIN_DEBUG_TAB
#       include <iostream>
#endif

Tab::Tab(
        double                   p_width           ,
        double                   p_height          ,
        double                   p_header_height   ,
        double                   p_header_start_pct,
        double                   p_header_end_pct  ,
        GLubyte                  p_r               ,
        GLubyte                  p_g               ,
        GLubyte                  p_b               ,
        GLubyte                  p_a               ,
        HUDElement::Highlighting p_highlighting    ,
        HUDElement *             p_parent          ,
        std::string              p_name            ,
        HUDElement::Visibility   p_visible         ,
        Triple                   p_pos             ,
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
        Window(
                p_highlighting,
                p_parent      ,
                p_name        ,
                p_visible     ,
                p_pos         ,
                p_ang
        ),
        FilledWindow(
                p_width       ,
                p_height      ,
                p_r           ,
                p_g           ,
                p_b           ,
                p_a           ,
                p_highlighting,
                p_parent      ,
                p_name        ,
                p_visible     ,
                p_pos         ,
                p_ang
        ),
        header(
                new FilledWindow(
                        PEKOMIN_ABS(p_header_end_pct - p_header_start_pct) * p_width,
                        p_header_height,
                        p_r, p_g, p_b, p_a,
                        HUDElement::Highlighting::none,
                        this,
                        p_name + "->header",
                        HUDElement::Visibility::visible,
                        Triple(
                                -p_width/2.0 + PEKOMIN_ABS(p_header_end_pct - p_header_start_pct) * p_width/2.0 + p_header_start_pct * p_width,
                                (p_header_height + p_height)/2.0,
                                0
                        )
                )
        ),
        header_height   (p_header_height   ),
        header_start_pct(p_header_start_pct),
        header_end_pct  (p_header_end_pct  )
{
#ifdef PEKOMIN_DEBUG_TAB
        std::cerr
                << "I’m "
                << static_cast<void *>(static_cast<HUDElement *>(this))
                << ", my header is "
                << static_cast<void *>(static_cast<HUDElement *>(header))
                << ", and my header’s parent is "
                << static_cast<void *>(header->parent)
                << std::endl;
#endif
}

void Tab::draw(GLuint active_hud_elem) const {
        if (visible == HUDElement::Visibility::hidden) return;

        glPushName(select_uid);
                glPushMatrix();
                        if (
                                highlighting == HUDElement::Highlighting::scale_wobble
                                && is(active_hud_elem)
                        ) {
                                glScalef(
                                        1 + PEKOMIN_HUD_HIGHLIGHT_SCALE * cos(PEKOMIN_HUD_HIGHLIGHT_SPEED * new_time) / width,
                                        1 + PEKOMIN_HUD_HIGHLIGHT_SCALE * cos(PEKOMIN_HUD_HIGHLIGHT_SPEED * new_time) / height,
                                        1
                                );
                        }

                        glTranslatef(
                                header->pos.x,
                                header->pos.y,
                                header->pos.z
                        );
                        glRotatef(
                                (header->ang * 180.0)/M_PI,
                                0, 0, 1
                        );
                        header->draw(active_hud_elem);
                glPopMatrix();

                FilledWindow::draw(active_hud_elem);
        glPopName();
}

void Tab::update(unsigned int ticks, unsigned int delta_ticks) {
        HUDElement::update(ticks, delta_ticks);
        header->update(ticks, delta_ticks);
        FilledWindow::update(ticks, delta_ticks);
}

Tab::~Tab() {
        delete header;
}

#define PEKOMIN_DEFINE_CALLBACK_SETTER(event)               \
        Tab & Tab::set_callback_##event(HUDCallback_t cb) { \
                header      ->set_callback_##event(cb);     \
                FilledWindow::set_callback_##event(cb);     \
                return *this;                               \
        }
PEKOMIN_EVENTS(PEKOMIN_DEFINE_CALLBACK_SETTER)
#undef PEKOMIN_DEFINE_CALLBACK_SETTER

HUDElement * Tab::is(GLuint uid) const {
        HUDElement * p;
        if ((p = FilledWindow::is(uid))) return p;
        if ((p = header      ->is(uid))) return p;
        return nullptr;
}

HUDElement * Tab::contains(GLuint uid) const {
        HUDElement * p;
        if ((p = FilledWindow::contains(uid))) return p;
        if ((p = header      ->contains(uid))) return p;
        return nullptr;
}

Tab & Tab::set_color(
        GLubyte r,
        GLubyte g,
        GLubyte b
) {
        FilledWindow::set_color(r, g, b);
        header      ->set_color(r, g, b);
        return *this;
}

Tab & Tab::set_opacity(GLubyte a) {
        FilledWindow::set_opacity(a);
        header      ->set_opacity(a);
        return *this;
}
