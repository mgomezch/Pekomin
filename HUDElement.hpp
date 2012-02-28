#ifndef PEKOMIN_HUDELEMENT_HPP
#define PEKOMIN_HUDELEMENT_HPP

#include <functional>
#include <GL/gl.h>
#include <string>
#include <tuple>
#include <vector>

#include "Triple.hpp"

class HUDElement {
        public:
                std::string name;
                Triple pos;
                double ang;

                Triple new_pos;
                double new_ang;

                std::function<void(HUDElement *)> leftclick;
                std::function<void(HUDElement *)> middleclick;
                std::function<void(HUDElement *)> rightclick;

                bool visible;

                GLuint select_uid;

                HUDElement(
                        std::string name    = "",
                        Triple      pos     = Triple(),
                        double      ang     = 0,
                        bool        visible = true
                );

                virtual ~HUDElement() = 0;

                virtual void draw() const = 0;
                virtual void update() = 0;

                const Triple orientation() const;

                virtual void set_leftclick  (std::function<void(HUDElement *)>);
                virtual void set_middleclick(std::function<void(HUDElement *)>);
                virtual void set_rightclick (std::function<void(HUDElement *)>);

                virtual bool identify(GLuint uid);
};

#endif
