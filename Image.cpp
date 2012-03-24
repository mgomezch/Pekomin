#include <algorithm>
#include <cmath>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <string>

#include "gl.hpp"
#include "game.hpp"
#include "Triple.hpp"

#include "HUDElement.hpp"
#include "Image.hpp"

#define PEKOMIN_DEBUG_IMAGE 1

#if PEKOMIN_DEBUG_IMAGE
#       include <iostream>
#endif

Image::Image(
        std::string              p_path        ,
        double                   p_width       ,
        double                   p_height      ,
        GLubyte                  p_opacity     ,
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
        width  (p_width  ),
        height (p_height ),
        opacity(p_opacity)
{
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        loadPNG(path.c_str(), &tw, &th, &ta, &texture_data);

        glTexImage2D(GL_TEXTURE_2D, 0, ta ? 4 : 3, tw, th, 0, ta ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, texture_data);
}

void Image::draw(GLuint active_hud_elem) const {
        if (visible == HUDElement::Visibility::hidden) return;

        glPushName(select_uid);
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

                        glTranslatef(
                                pos.x,
                                pos.y,
                                pos.z
                        );
                        glRotatef(
                                (ang * 180.0)/M_PI,
                                0, 0, 1
                        );
                        glScalef(width, height, 1);

                        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
                        glBindTexture(GL_TEXTURE_2D, taceptar);
                        glEnable(GL_TEXTURE_2D);
                        glCallList(cuadrado_simple);
                        glDisable(GL_TEXTURE_2D);
                glPopMatrix();
        glPopName();
}

void Image::update() {}

Image & Image::set_opacity(GLubyte p_opacity) {
        opacity = p_opacity;
        return *this;
}
