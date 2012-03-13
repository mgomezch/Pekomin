#ifndef PEKOMIN_FILLEDWINDOW_HPP
#define PEKOMIN_FILLEDWINDOW_HPP

#include <GL/gl.h>
#include <list>
#include <string>

#include "Triple.hpp"
#include "Window.hpp"

class FilledWindow : public virtual Window {
        public:
                double width, height;
                GLubyte color[4];

                FilledWindow(
                        double                   p_width                                         ,
                        double                   p_heigh                                         ,
                        GLubyte                  p_r            = 255                            ,
                        GLubyte                  p_g            = 255                            ,
                        GLubyte                  p_b            = 255                            ,
                        GLubyte                  p_a            = 255                            ,
                        HUDElement::Highlighting p_highlighting = HUDElement::Highlighting::none ,
                        HUDElement *             p_parent       = nullptr                        ,
                        std::string              p_name         = ""                             ,
                        HUDElement::Visibility   p_visible      = HUDElement::Visibility::visible,
                        Triple                   p_pos          = Triple()                       ,
                        double                   p_ang          = 0
                );

                virtual void draw(GLuint active_hud_elem) const;

                virtual FilledWindow & set_color(
                        GLubyte r,
                        GLubyte g,
                        GLubyte b
                );

                virtual FilledWindow & set_opacity(GLubyte a);
};

#endif
