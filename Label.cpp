#include <algorithm>
#include <cmath>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <string>

#include "game.hpp"
#include "gl.hpp"
#include "HUDElement.hpp"
#include "Triple.hpp"
#include "Label.hpp"

#define PEKOMIN_DEBUG_LABEL 1

#if PEKOMIN_DEBUG_LABEL
#       include <iostream>
#endif

Label::Label(
        std::string              p_text        ,
        GLfloat                  p_scale       ,
        GLfloat                  p_thickness   ,
        GLubyte                  p_r           ,
        GLubyte                  p_g           ,
        GLubyte                  p_b           ,
        GLubyte                  p_a           ,
        Alignment                p_alignment   ,
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
        text     (p_text             ),
        scale    (p_scale            ),
        thickness(p_thickness        ),
        color    {p_r, p_g, p_b, p_a },
        alignment(p_alignment        )
{}

void Label::draw(GLuint active_hud_elem) const {
        if (visible == HUDElement::Visibility::hidden) return;

        int width = glutStrokeLength(
                GLUT_STROKE_ROMAN,
                reinterpret_cast<const unsigned char *>(text.c_str())
        );
        int height = glutStrokeHeight(GLUT_STROKE_ROMAN);

        glPushName(select_uid);
                glPushMatrix();
                        glTranslatef(
                                pos.x,
                                pos.y,
                                pos.z
                        );
                        glRotatef(
                                (ang * 180.0)/M_PI,
                                0, 0, 1
                        );

                        glColor4ubv(color);

                        glLineWidth(
                                thickness
                                + (
                                        highlighting == HUDElement::Highlighting::scale_wobble && is(active_hud_elem)
                                        ? PEKOMIN_HUD_HIGHLIGHT_SCALE * cos(PEKOMIN_HUD_HIGHLIGHT_SPEED * new_time)
                                        : 0
                                )
                        );

                        glScalef(scale, scale, scale);

                        glTranslatef(0, -height/2.0, 0);
                        if (alignment == Alignment::center) glTranslatef(-width/2.0, 0, 0);

                        glutStrokeString(
                                GLUT_STROKE_ROMAN,
                                reinterpret_cast<const unsigned char *>(text.c_str())
                        );
                glPopMatrix();
        glPopName();
}

void Label::update() {}

Label & Label::set_color(
        GLubyte r,
        GLubyte g,
        GLubyte b
) {
        color[0] = r;
        color[1] = g;
        color[2] = b;
        return *this;
}

Label & Label::set_opacity(GLubyte a) {
        color[3] = a;
        return *this;
}
