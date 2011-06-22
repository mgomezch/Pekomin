#ifndef _NODE_HPP
#define _NODE_HPP

#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include "Triple.hpp"
#include "Ent.hpp"

using namespace std;

class Node : public Ent {
        public:
                vector<tuple<Node*, bool, double> > adj;

                Node(string name = "", Triple pos = Triple());

                void add_adj(tuple<Node*, bool, double> node);
                bool is_adj(Node *adj);
                void print_node();
                void print_adj();

                virtual void draw();
                virtual void update(unsigned int ticks);
};

#endif
