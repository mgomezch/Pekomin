#include "Face.hpp"
#include "Mobile.hpp"

pair<Triple, double> Face::getSteering() {
        Triple direction;

        direction = target->pos - character->pos;

        if (direction.length() > 0) {
                Align::target = target;
                // WTF?
                //Align::target->orientation = atan2(-direction.x, direction.z);
        }

        return Align::getSteering();
}
