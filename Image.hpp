#ifndef PEKOMIN_IMAGE_HPP
#define PEKOMIN_IMAGE_HPP

#include <GL/gl.h>
#include <string>

#include "gl.hpp"
#include "Triple.hpp"

#include "HUDElement.hpp"

class Image : public virtual HUDElement {
        public:
                std::string path        ;
                double      width       ;
                double      height      ;
                GLubyte     opacity     ;
                GLubyte *   texture_data;
                GLuint      texture     ;

                int tw;
                int th;
                int ta;

                Image(
                        std::string              p_path                                          ,
                        double                   p_width                                         ,
                        double                   p_height                                        ,
                        GLubyte                  p_opacity      = 255                            ,
                        HUDElement::Highlighting p_highlighting = HUDElement::Highlighting::none ,
                        HUDElement *             p_parent       = nullptr                        ,
                        std::string              p_name         = ""                             ,
                        HUDElement::Visibility   p_visible      = HUDElement::Visibility::visible,
                        Triple                   p_pos          = Triple()                       ,
                        double                   p_ang          = 0
                );

                virtual void draw(GLuint active_hud_elem) const;

                virtual Image & set_opacity(GLubyte p_opacity);
};

#endif
