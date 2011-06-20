#include "Node.hpp"

#include "gl.hpp"
#include <GL/glut.h>

Node::Node() {
        this->id    = "";
        this->check = false;
        this->pos   = Triple(0, 0, 0);
        this->ang   = 0;
        this->vel   = Triple(0, 0, 0);
        this->vrot  = 0;
}

Node::Node(Triple pos) {
        this->id    = "";
        this->check = false;
        this->pos   = pos;
        this->ang   = 0;
        this->vel   = Triple(0, 0, 0);
        this->vrot  = 0;
}

Node::Node(string id, Triple pos) {
        this->id    = id;
        this->check = false;
        this->pos   = pos;
        this->ang   = 0;
        this->vel   = Triple(0, 0, 0);
        this->vrot  = 0;
}

Triple Node::get_Pos(){
        return this->pos;
}

bool Node::is_Visited() {
        return this->check;
}

void Node::add_adj(tuple<Node *, bool, double> node) {
        adj.push_back(node);
}

bool Node::is_adj(Node *n) {
        tuple<Node*, bool, double> node;
        for (unsigned int i = 0; i < adj.size(); i++) {
                node = adj[i];
                if (get<0>(node) == n)
                        return true;
        }
        return false;
}

void Node::print_node() {
        cout << "Node : " << this << " id : " << this->id << " Position : (" << this->pos.x << ", " << this->pos.y << ", "<< this->pos.z << ")" << endl;
}

void Node::print_adj() {
        this->print_node();
        cout << "\tAdjacency Nodes: " << endl;
        tuple <Node*, bool, double> node;
        for (unsigned int i = 0; i < adj.size(); i++) {
                node = adj[i];
                cout << "\tNode : " << get<0>(node) << " id : " << get<0>(node)->id << " Position : (" << get<0>(node)->pos.x << ", " << get<0>(node)->pos.y << ", " << get<0>(node)->pos.z << ")" << " distance : "<< get<2>(node) << endl;
        }
}

void Node::draw() {
        glPushMatrix();
                glColor4ub(255, 255, 0, 255);
                glTranslatef(0, 0, 0.5);
                glCallList(cubo);
                /*glBegin(GL_LINES);
                        glVertex3f(0, 0, 0);
                        glVertex3f(2, 0, 0);
                glEnd();*/
        glPopMatrix();
}

void Node::update(unsigned int ticks) {}
