#ifndef PEKOMIN_RADIALMENU_HPP
#define PEKOMIN_RADIALMENU_HPP

#include <cmath>
#include <GL/gl.h>
#include <string>

#include "HUDElement.hpp"
#include "Triple.hpp"

class RadialMenu : public virtual HUDElement {
        public:
                enum class Hideable : unsigned int {
                        yes,
                        no
                };

                enum class Alignment : unsigned int {
                        horizontal,
                        tangential
                };

                HUDElement *              controller    ;
                double                    radius        ;
                double                    angle_start   ;
                double                    angle_end     ;
                double                    speed         ;
                bool                      active        ;
                Alignment                 alignment     ;
                HUDCallback_t             show_callback ;
                HUDCallback_t             hide_callback ;
                Hideable                  hideable      ;

                std::vector<HUDElement *> children;

                RadialMenu(
                        HUDElement *             p_controller                                     ,
                        double                   p_radius                                         ,
                        double                   p_angle_start   = 0                              ,
                        double                   p_angle_end     = 360                            ,
                        double                   p_speed         = 0.01                           ,
                        bool                     p_active        = false                          ,
                        Alignment                p_alignment     = Alignment::horizontal          ,
                        HUDCallback_t            p_show_callback = nullptr                        ,
                        HUDCallback_t            p_hide_callback = nullptr                        ,
                        Hideable                 p_hideable      = Hideable::yes                  ,
                        HUDElement::Highlighting p_highlighting  = HUDElement::Highlighting::none ,
                        HUDElement *             p_parent        = nullptr                        ,
                        std::string              p_name          = ""                             ,
                        HUDElement::Visibility   p_visible       = HUDElement::Visibility::visible,
                        Triple                   p_pos           = Triple()                       ,
                        double                   p_ang           = 0
                );

                virtual void draw(GLuint active_hud_elem) const;
                virtual void update(unsigned int ticks, unsigned int delta_ticks);

                virtual HUDElement * contains(GLuint uid) const;

        protected:
                double current_radius;
                double radius_t;
};

#endif
