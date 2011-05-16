#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "Behaviors.hpp"
#include "game.hpp"
#include "Mobile.hpp"
#include "parse.hpp"
#include "Player.hpp"
#include "RuntimePekomin.hpp"

#define DEBUG_PARSE

using namespace std;

unordered_map<string, Mobile *> entses;
unordered_map<string, unordered_map<string, unordered_map<string, string> *> *> behaviorses;

void parse_r(char *s, int chars) {
        unsigned int n;
        char   *name  , *type  , *field  , *value  ;
        string  name_s,  type_s,  field_s,  value_s;
        unordered_map<string, string> fields = unordered_map<string, string>();
        unordered_map<string, unordered_map<string, string> *> *behaviors = new unordered_map<string, unordered_map<string, string> *>();
        unordered_map<string, string>::const_iterator it;
        int nextchars;
        Mobile *ent;

#ifdef DEBUG_PARSE
        cout << "parse: starting at " << static_cast<void *>(s) << " + " << chars << endl;
#endif

        switch (sscanf(s + chars, " %ms %n", &name, &nextchars)) {
                case 0:
                        cerr << "parse error reading name" << endl;
                        exit(EX_DATAERR);
                case EOF:
                        return;
                default:
                        chars += nextchars;
        }
#ifdef DEBUG_PARSE
        cout << "parse: read ent name " << name_s << endl;
#endif
        name_s = string(name);
        free(name);

        nextchars = -1;
        switch(sscanf(s + chars, " { %n", &nextchars)) {
                case 0:
                case EOF:
                        if (nextchars == -1) {
                                cerr << "parse error reading ent " << name_s << ": expected '{'" << endl;
                                exit(EX_DATAERR);
                        }
                default:
                        chars += nextchars;
        }
#ifdef DEBUG_PARSE
        printf("parse: entering ent %s\n", name);
#endif

        while (nextchars = -1, sscanf(s + chars, " } %n", &nextchars), nextchars == -1) {
                // Field
                field = value = NULL;
                if (sscanf(s + chars, " %m[a-zA-Z_0-9.] = %m[a-zA-Z_0-9.] ;%n", &field, &value, &nextchars) >= 2) {
                        chars += nextchars;
                        field_s = string(field);
                        free(field);
                        value_s = string(value);
                        free(value);
#ifdef DEBUG_PARSE
                        cout << "        parse: ent " << name_s << ": found field: " << field_s << " = " << value_s << endl;
#endif
                        fields[field_s] = value_s;
                }

                // Behavior
                else if (sscanf(s + chars, " %ms { %n", &type, &nextchars) >= 1) {
                        chars += nextchars;
                        type_s = string(type);
                        free(type);
#ifdef DEBUG_PARSE
                        cout << "        parse: ent " << name_s << ": found behavior: " << type_s << "; entering" << endl;
#endif

                        (*behaviors)[type_s] = new unordered_map<string, string>();
                        while (nextchars = -1, sscanf(s + chars, " } %n", &nextchars), nextchars == -1) {
                                field = value = NULL;
                                if (sscanf(s + chars, " %m[a-zA-Z_0-9.] = %m[a-zA-Z_0-9.] ; %n", &field, &value, &nextchars) >= 2) {
                                        chars += nextchars;
                                        field_s = string(field);
                                        free(field);
                                        value_s = string(value);
                                        free(value);
                                        (*((*behaviors)[type_s]))[field_s] = value_s;
#ifdef DEBUG_PARSE
                                        cout << "                parse: ent " << name_s << ": behavior " << type_s << ": found field: " << field_s << " = " << value_s << endl;
#endif
                                } else {
                                        cerr << "parse error reading ent " << name_s << ", behavior " << type_s << ": expected field or '}'" << endl;
                                        exit(EX_DATAERR);
                                }
                        }
                        chars += nextchars;
#ifdef DEBUG_PARSE
                        cout << "        parse: ent " << name_s << ": leaving behavior " << type_s << endl;
#endif
                }

                // Error
                else {
                        cerr << "parse error reading ent " << name_s << ": expected field, behavior or '}'" << endl;
                        exit(EX_DATAERR);
                }
        }
        chars += nextchars;
#ifdef DEBUG_PARSE
                        cout << "parse: leaving ent " << name_s << endl; // DEBUG
#endif

        if (name_s == "player") {
                if (player != NULL) {
                        cerr << "parse error: player already defined" << endl;
                        exit(EX_DATAERR);
                }
                ent = player = new Player();
        } else {
                ent = new RuntimePekomin();
                ents.push_back(ent);
        }

        it = fields.find("pos.x");
        if (it != fields.end()) {
                if (sscanf(it->second.c_str(), "%i", &n) != 1) {
                        cerr << "parse error reading ent field pos.x = " << it->second << endl;
                        exit(EX_DATAERR);
                }
                ent->pos.x = n;
        }
        it = fields.find("pos.y");
        if (it != fields.end()) {
                if (sscanf(it->second.c_str(), "%i", &n) != 1) {
                        cerr << "parse error reading ent field pos.y = " << it->second << endl;
                        exit(EX_DATAERR);
                }
                ent->pos.y = n;
        }
        it = fields.find("pos.z");
        if (it != fields.end()) {
                if (sscanf(it->second.c_str(), "%i", &n) != 1) {
                        cerr << "parse error reading ent field pos.z = " << it->second << endl;
                        exit(EX_DATAERR);
                }
                ent->pos.z = n;
        }
        it = fields.find("vel.x");
        if (it != fields.end()) {
                if (sscanf(it->second.c_str(), "%i", &n) != 1) {
                        cerr << "parse error reading ent field vel.x = " << it->second << endl;
                        exit(EX_DATAERR);
                }
                ent->vel.x = n;
        }
        it = fields.find("vel.y");
        if (it != fields.end()) {
                if (sscanf(it->second.c_str(), "%i", &n) != 1) {
                        cerr << "parse error reading ent field vel.y = " << it->second << endl;
                        exit(EX_DATAERR);
                }
                ent->vel.y = n;
        }
        it = fields.find("vel.z");
        if (it != fields.end()) {
                if (sscanf(it->second.c_str(), "%i", &n) != 1) {
                        cerr << "parse error reading ent field vel.z = " << it->second << endl;
                        exit(EX_DATAERR);
                }
                ent->vel.z = n;
        }

        entses[name_s]      = ent      ;
        behaviorses[type_s] = behaviors;

        fields.erase(fields.begin(), fields.end());

        parse_r(s, chars);
}

void parse(char *s) {
        unordered_map<string, string                                                  >::const_iterator it_fields;
        unordered_map<string, Mobile *                                                >::const_iterator it_entses;
        unordered_map<string, unordered_map<string, unordered_map<string, string> *> *>::const_iterator it_e;
                              unordered_map<string, unordered_map<string, string> *>   ::const_iterator it_b;
        RuntimePekomin *p;

        parse_r(s, 0);

        for (it_e = behaviorses.begin(); it_e != behaviorses.end(); ++it_e) {
                if (it_e->first == "player") continue;
                for (it_b = it_e->second->begin(); it_b != it_e->second->end(); ++it_b) {

                        // Align(Mobile *character, Mobile *target, double maxAngularAcceleration, double maxRotation, double targetRadius, double slowRadius);
                        if (it_b->first == "Align") {
                                Mobile *character;
                                it_entses = entses.find(it_e->first);
                                if (it_entses != entses.end()) {
                                        character = it_entses->second;
                                } else {
                                        // this should never happen
                                        cerr << "parse error making ent '" << it_e->first << "' behavior '" << it_b->first << "': ent '" << it_e->first << "' not found" << endl;
                                        exit(EX_SOFTWARE);
                                }

                                Mobile *target;
                                it_fields = it_b->second->find(string("target"));
                                if (it_fields != it_b->second->end()) {
                                        it_entses = entses.find(it_fields->second);
                                        if (it_entses != entses.end()) {
                                                target = it_entses->second;
                                        } else {
                                                cerr << "parse error making ent '" << it_e->first << "' behavior '" << it_b->first << "': field 'target' == '" << it_fields->second << "': ent not found" << endl;
                                                exit(EX_DATAERR);
                                        }
                                } else {
                                        cerr << "parse error making ent '" << it_e->first << "' behavior '" << it_b->first << "': required field 'target' not specified" << endl;
                                        exit(EX_DATAERR);
                                }

                                double maxAngularAcceleration;
                                it_fields = it_b->second->find(string("maxAngularAcceleration"));
                                if (it_fields != it_b->second->end()) {
                                        if (sscanf(it_fields->second.c_str(), "%lf", &maxAngularAcceleration) != 1) {
                                                cerr << "parse error making ent '" << it_e->first << "' behavior '" << it_b->first << "': required field 'maxAngularAcceleration' == '" << it_fields->second << "' not a floating-point number" << endl;
                                                exit(EX_DATAERR);
                                        }
                                } else {
                                        cerr << "parse error making ent '" << it_e->first << "' behavior '" << it_b->first << "': required field 'maxAngularAcceleration' not specified" << endl;
                                        exit(EX_DATAERR);
                                }

                                double maxRotation;
                                it_fields = it_b->second->find(string("maxRotation"));
                                if (it_fields != it_b->second->end()) {
                                        if (sscanf(it_fields->second.c_str(), "%lf", &maxRotation) != 1) {
                                                cerr << "parse error making ent '" << it_e->first << "' behavior '" << it_b->first << "': required field 'maxRotation' == '" << it_fields->second << "' not a floating-point number" << endl;
                                                exit(EX_DATAERR);
                                        }
                                } else {
                                        cerr << "parse error making ent '" << it_e->first << "' behavior '" << it_b->first << "': required field 'maxRotation' not specified" << endl;
                                        exit(EX_DATAERR);
                                }

                                double targetRadius;
                                it_fields = it_b->second->find(string("targetRadius"));
                                if (it_fields != it_b->second->end()) {
                                        if (sscanf(it_fields->second.c_str(), "%lf", &targetRadius) != 1) {
                                                cerr << "parse error making ent '" << it_e->first << "' behavior '" << it_b->first << "': required field 'targetRadius' == '" << it_fields->second << "' not a floating-point number" << endl;
                                                exit(EX_DATAERR);
                                        }
                                } else {
                                        cerr << "parse error making ent '" << it_e->first << "' behavior '" << it_b->first << "': required field 'targetRadius' not specified" << endl;
                                        exit(EX_DATAERR);
                                }

                                double slowRadius;
                                it_fields = it_b->second->find(string("slowRadius"));
                                if (it_fields != it_b->second->end()) {
                                        if (sscanf(it_fields->second.c_str(), "%lf", &slowRadius) != 1) {
                                                cerr << "parse error making ent '" << it_e->first << "' behavior '" << it_b->first << "': required field 'slowRadius' == '" << it_fields->second << "' not a floating-point number" << endl;
                                                exit(EX_DATAERR);
                                        }
                                } else {
                                        cerr << "parse error making ent '" << it_e->first << "' behavior '" << it_b->first << "': required field 'slowRadius' not specified" << endl;
                                        exit(EX_DATAERR);
                                }

                                p = dynamic_cast<RuntimePekomin *>(character);
                                if (p == NULL) {
                                        // this should never happen
                                        cerr << "parse error making ent '" << it_e->first << "' behavior '" << it_b->first << "': ent '" << it_e->first << "' is not RuntimePekomin" << endl;
                                        exit(EX_SOFTWARE);
                                }
                                p->addBehavior(new Align(character, target, maxAngularAcceleration, maxRotation, targetRadius, slowRadius));
                        }
/*
                        TODO: for each behavior: parse fields, instantiate behavior, set fields, add to ent.
                        Arrive(Mobile *character, Mobile *target, double maxAcceleration, double maxSpeed, double targetRadius, double slowRadius);
                        Evade(Mobile *character, Mobile *target, double maxAcceleration);
                        Face(Mobile *character, Mobile *target, double maxAngularAcceleration, double maxRotation, double targetRadius, double slowRadius);
                        Flee(Mobile *character, Mobile *target, double maxAcceleration);
                        KinematicArrive(Ent *character, Ent *target, double maxSpeed, double radius);
                        KinematicFlee(Ent *character, Ent *target, double maxSpeed);
                        KinematicSeek(Ent *character, Ent *target, double maxSpeed);
                        KinematicWander(Ent *character, double maxSpeed, double maxRotation);
                        LookWhereYoureGoing(Mobile *character, Mobile *target, double maxAngularAcceleration, double maxRotation, double targetRadius, double slowRadius);
                        Pursue(Mobile *character, Mobile *target, double maxAcceleration);
                        Seek(Mobile *character, Mobile *target, double maxAcceleration);
                        Separation(Mobile *character, Mobile *target, double threshold, double decayCoefficient, double maxAcceleration);
                        VelocityMatch(Mobile *character, Mobile *target, double maxAcceleration);
                        Wander(Mobile *character, Mobile *target, double maxAngularAcceleration, double maxRotation, double targetRadius, double slowRadius, double wanderOffset, double wanderRadius, double wanderRate, double wanderOrientation, double maxAcceleration);
*/
                }
        }

        // TODO: DELETE HEAP GARBAGE: delete behaviorses and entses.
}

