#include <vector>
#include <tuple>
#include <iostream>

#include <GL/glut.h>
#include "gl.hpp"

#include "Node.hpp"

Node::Node(std::string name, Triple pos):
        Ent(name, pos)
{}

void Node::add_adj(Node *node) {
        adj.push_back(node);
}

bool Node::is_adj(Node *node) {
        for (auto it = adj.begin(); it != adj.end(); ++it) {
                if ((*it) == node) return true;
        }
        return false;
}

void Node::print_node() {
        std::cout << "Node " << static_cast<void *>(this) << ": name == " << this->name << "; pos == (" << this->pos.x << ", " << this->pos.y << ", " << this->pos.z << ")" << std::endl;
}

void Node::print_adj() {
        this->print_node();
        std::cout << "\tAdjacency nodes:" << std::endl;
        Node *node;
        for (auto it = adj.begin(); it != adj.end(); ++it) {
                node = (*it);
                std::cout << "\tNode " << static_cast<void *>(node) << ": name == " << node->name << "; pos == (" << node->pos.x << ", " << node->pos.y << ", " << node->pos.z << ")" << std::endl;
        }
}

void Node::add_mod(Ent *e, double c){
        std::tuple<Ent *, double> mod;
        std::get<0>(mod) = e;
        std::get<1>(mod) = c;
        mods.push_back(mod);
}

void Node::draw() {
        glPushMatrix();
                glColor4ub(255, 255, 0, 255);
                // TODO: no usar glutSolidSphere!!!
                glScalef(1, 1, 0.2);
                glutSolidSphere(0.5, 4, 4);
//              glCallList(cubo);
//              glBegin(GL_LINES);
//                      glVertex3f(0, 0, 0);
//                      glVertex3f(2, 0, 0);
//              glEnd();
        glPopMatrix();
}

void Node::steer(unsigned int ticks, unsigned int delta_ticks) {}

void Node::update() {}

std::tuple<Triple, Triple> points(Node *n1, Node *n2) {
        return std::make_tuple(n1->pos, n2->pos);
}
