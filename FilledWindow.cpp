#include <cmath>
#include <GL/gl.h>
#include <string>

#include "FilledWindow.hpp"
#include "game.hpp"
#include "gl.hpp"
#include "HUDElement.hpp"
#include "Triple.hpp"
#include "Window.hpp"

FilledWindow::FilledWindow(
        double                   p_width       ,
        double                   p_height      ,
        GLubyte                  p_r           ,
        GLubyte                  p_g           ,
        GLubyte                  p_b           ,
        GLubyte                  p_a           ,
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
        ),
        Window(
                p_highlighting,
                p_parent      ,
                p_name        ,
                p_visible     ,
                p_pos         ,
                p_ang
        ),
        width (p_width ),
        height(p_height),
        color {p_r, p_g, p_b, p_a}
{}

void FilledWindow::draw(GLuint active_hud_elem) const {
        if (visible == HUDElement::Visibility::hidden) return;

        glPushMatrix();
                glPushName(select_uid);
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
                        glPushName(select_uid);
                                glPushMatrix();
                                        glScalef(width, height, 1);
                                        glColor4ubv(color);
                                        glCallList(cuadrado_simple);
                                glPopMatrix();
                        glPopName();
                glPopName();

                Window::draw(active_hud_elem);
        glPopMatrix();
}

FilledWindow & FilledWindow::set_color(
        GLubyte r,
        GLubyte g,
        GLubyte b
) {
        color[0] = r;
        color[1] = g;
        color[2] = b;
        return *this;
}

FilledWindow & FilledWindow::set_opacity(GLubyte a) {
        color[3] = a;
        return *this;
}
