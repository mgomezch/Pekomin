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
                void print_node();
                void print_adj();

                virtual void draw();
                virtual void update(unsigned int ticks);
};

#endif
