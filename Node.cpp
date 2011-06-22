#include "Node.hpp"

#include "gl.hpp"
#include <GL/glut.h>

Node::Node(string name, Triple pos):
        Ent(name, pos, 0)
{}

void Node::add_adj(tuple<Node*, bool, double> node) {
        adj.push_back(node);
}

bool Node::is_adj(Node *n) {
        tuple<Node*, bool, double> node;
        for (unsigned int i = 0; i < adj.size(); i++) {
                node = adj[i];
                if (get<0>(node) == n) return true;
        }
        return false;
}

void Node::print_node() {
        cout << "Node " << static_cast<void *>(this) << ": name == " << this->name << "; pos == (" << this->pos.x << ", " << this->pos.y << ", " << this->pos.z << ")" << endl;
}

void Node::print_adj() {
        this->print_node();
        cout << "\tAdjacency nodes:" << endl;
        tuple <Node*, bool, double> node;
        for (unsigned int i = 0; i < adj.size(); i++) {
                node = adj[i];
                cout << "\tNode " << static_cast<void *>(get<0>(node)) << ": name == " << get<0>(node)->name << "; pos == (" << get<0>(node)->pos.x << ", " << get<0>(node)->pos.y << ", " << get<0>(node)->pos.z << ")" << " distance == " << get<2>(node) << endl;
        }
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

void Node::update(unsigned int ticks) {}
