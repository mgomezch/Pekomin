#ifndef PEKOMIN_LABEL_HPP
#define PEKOMIN_LABEL_HPP

#include <GL/gl.h>
#include <list>
#include <string>

#include "HUDElement.hpp"
#include "Triple.hpp"

class Label : public virtual HUDElement {
        public:
                enum class Alignment : unsigned int {
                        left,
                        center
                };

                std::string text;
                GLfloat scale;
                GLfloat thickness;
                GLubyte color[4];
                Alignment alignment;

                Label(
                        std::string              p_text                                          ,
                        GLfloat                  p_scale        = 0.01                           ,
                        GLfloat                  p_thickness    = 2                              ,
                        GLubyte                  p_r            = 255                            ,
                        GLubyte                  p_g            = 255                            ,
                        GLubyte                  p_b            = 255                            ,
                        GLubyte                  p_a            = 255                            ,
                        Alignment                p_alignment    = Alignment::left                ,
                        HUDElement::Highlighting p_highlighting = HUDElement::Highlighting::none ,
                        HUDElement *             p_parent       = nullptr                        ,
                        std::string              p_name         = ""                             ,
                        HUDElement::Visibility   p_visible      = HUDElement::Visibility::visible,
                        Triple                   p_pos          = Triple()                       ,
                        double                   p_ang          = 0
                );

                virtual void draw(GLuint active_hud_elem) const;
                virtual void update();

                virtual Label & set_color(
                        GLubyte r,
                        GLubyte g,
                        GLubyte b
                );

                virtual Label & set_opacity(GLubyte a);
};

#endif
