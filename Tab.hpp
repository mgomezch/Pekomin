#ifndef PEKOMIN_TAB_HPP
#define PEKOMIN_TAB_HPP

#include <GL/gl.h>
#include <string>

#include "FilledWindow.hpp"
#include "Triple.hpp"

class Tab : public virtual FilledWindow {
        public:
                FilledWindow * header;

                double header_height;
                double header_start_pct;
                double header_end_pct;

                Tab(
                        double                   p_width                                             ,
                        double                   p_height                                            ,
                        double                   p_header_height                                     ,
                        double                   p_header_start_pct                                  ,
                        double                   p_header_end_pct                                    ,
                        GLubyte                  p_r                = 255                            ,
                        GLubyte                  p_g                = 255                            ,
                        GLubyte                  p_b                = 255                            ,
                        GLubyte                  p_a                = 255                            ,
                        HUDElement::Highlighting p_highlighting     = HUDElement::Highlighting::none ,
                        HUDElement *             p_parent           = NULL                           ,
                        std::string              p_name             = ""                             ,
                        HUDElement::Visibility   p_visible          = HUDElement::Visibility::visible,
                        Triple                   p_pos              = Triple()                       ,
                        double                   p_ang              = 0
                );

                virtual ~Tab();

                virtual void draw(GLuint active_hud_elem) const;
                virtual void update();

#define PEKOMIN_DECLARE_CALLBACK_SETTER(event) Tab & set_callback_##event(HUDCallback_t cb);
                PEKOMIN_EVENTS(PEKOMIN_DECLARE_CALLBACK_SETTER)
#undef PEKOMIN_DECLARE_CALLBACK_SETTER

                virtual HUDElement * is(GLuint uid) const;

                virtual HUDElement * contains(GLuint uid) const;

                virtual Tab & set_color(GLubyte r, GLubyte g, GLubyte b);

                virtual Tab & set_opacity(GLubyte a);
};

#endif
