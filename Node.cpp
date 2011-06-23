#include "Node.hpp"

#include "gl.hpp"
#include <GL/glut.h>

Node::Node(string name, Triple pos):
        Ent(name, pos, 0)
{}

void Node::add_adj(Node *node) {
        adj.push_back(node);
}

bool Node::is_adj(Node *node) {
        Node *n;

        for (unsigned int i = 0; i < adj.size(); i++) {
                n = adj[i];
                if (n == node) return true;
        }
        return false;
}

void Node::print_node() {
        cout << "Node " << static_cast<void *>(this) << ": name == " << this->name << "; pos == (" << this->pos.x << ", " << this->pos.y << ", " << this->pos.z << ")" << endl;
}

void Node::print_adj() {
        this->print_node();
        cout << "\tAdjacency nodes:" << endl;
        Node *node;
        for (unsigned int i = 0; i < adj.size(); i++) {
                node = adj[i];
                cout << "\tNode " << static_cast<void *>(node) << ": name == " << node->name << "; pos == (" << node->pos.x << ", " << node->pos.y << ", " << node->pos.z << ")" << endl;
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
