#ifndef PEKOMIN_TABS_HPP
#define PEKOMIN_TABS_HPP

#include <GL/gl.h>
#include <string>

#include "HUDElement.hpp"
#include "Triple.hpp"

class Tabs : public virtual HUDElement {
        public:
                double width;
                double height;
                double header_height;
                std::vector<FilledWindow *> pages;
                std::vector<FilledWindow *> headers;
                FilledWindow * active_page;

                Tabs(
                        double                   p_width                                             ,
                        double                   p_heigh                                             ,
                        double                   p_header_height                                     ,
                        unsigned int             p_pages            = 0                              ,
                        GLubyte                  p_r                = 255                            ,
                        GLubyte                  p_g                = 255                            ,
                        GLubyte                  p_b                = 255                            ,
                        GLubyte                  p_a                = 255                            ,
                        HUDElement::Highlighting p_highlighting     = HUDElement::Highlighting::none ,
                        HUDElement *             p_parent           = nullptr                        ,
                        std::string              p_name             = ""                             ,
                        HUDElement::Visibility   p_visible          = HUDElement::Visibility::visible,
                        Triple                   p_pos              = Triple()                       ,
                        double                   p_ang              = 0
                );

                virtual void draw(GLuint active_hud_elem) const;
                virtual void update();

                virtual HUDElement * contains(GLuint uid) const;
};

#endif
