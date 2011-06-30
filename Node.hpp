#ifndef _NODE_HPP
#define _NODE_HPP

#include <iostream>
#include <string>
#include <vector>

#include "Ent.hpp"
#include "Triple.hpp"

using namespace std;

class Node : public Ent {
        public:
                vector<Node*> adj;

                Node(string name = "", Triple pos = Triple());

                void add_adj(Node *node);
                bool is_adj(Node *adj);
                void print_adj();
                void print_node();

                virtual void draw();
                virtual void steer(unsigned int ticks);
                virtual void update();
};

#endif
