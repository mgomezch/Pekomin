#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <vector>

#include "Ent.hpp"
#include "Triple.hpp"

class Node : public Ent {
        public:
                std::vector<Node *> adj;

                Node(std::string name = "", Triple pos = Triple());

                void add_adj(Node *node);
                bool is_adj(Node *adj);
                void print_adj();
                void print_node();

                virtual void draw();
                virtual void steer(unsigned int ticks, unsigned int delta_ticks);
                virtual void update();
};

#endif
