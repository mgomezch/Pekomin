#ifndef PEKOMIN_HUDELEMENT_HPP
#define PEKOMIN_HUDELEMENT_HPP

#include <functional>
#include <GL/gl.h>
#include <list>
#include <string>

#include "events.hpp"
#include "Triple.hpp"

class HUDElement;

typedef std::function<void (HUDElement *)> HUDCallback_t;

class HUDElement {
        public:
                enum class Visibility : unsigned int {
                        visible,
                        hidden
                };

                enum class Highlighting : unsigned int {
                        none,
                        scale_wobble
                };

                Highlighting highlighting;
                HUDElement * parent      ;
                std::string  name        ;
                Visibility   visible     ;
                Triple       pos         ;
                double       ang         ;

                Triple       new_pos     ;
                double       new_ang     ;

#define PEKOMIN_DECLARE_CALLBACK_MEMBER(event) HUDCallback_t callback_##event;
                PEKOMIN_EVENTS(PEKOMIN_DECLARE_CALLBACK_MEMBER)
#undef PEKOMIN_DECLARE_CALLBACK_MEMBER

                std::list<HUDCallback_t> update_callbacks;

                GLuint select_uid;

                HUDElement(
                        Highlighting p_highlighting = Highlighting::none ,
                        HUDElement * p_parent       = nullptr            ,
                        std::string  p_name         = ""                 ,
                        Visibility   p_visible      = Visibility::visible,
                        Triple       p_pos          = Triple()           ,
                        double       p_ang          = 0
                );

                virtual ~HUDElement() = 0;

                virtual void draw(GLuint active_hud_elem) const = 0;
                virtual void update(unsigned int ticks, unsigned int delta_ticks);

#define PEKOMIN_DECLARE_CALLBACK_SETTER(event) HUDElement & set_callback_##event(HUDCallback_t cb);
                PEKOMIN_EVENTS(PEKOMIN_DECLARE_CALLBACK_SETTER)
#undef PEKOMIN_DECLARE_CALLBACK_SETTER

                HUDElement & add_update_callback(HUDCallback_t cb);

                virtual HUDElement * is(GLuint uid) const;

                virtual HUDElement * contains(GLuint uid) const;
};

#endif
