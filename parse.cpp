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
#include "Phantom.hpp"
#include "RuntimePekomin.hpp"

#define DEBUG_PARSE

#ifdef DEBUG_PARSE
        #define SET_ENT_FIELD_DOUBLE(FIELD)                              \
                it = fields.find(string( #FIELD ));                      \
                if (it != fields.end()) {                                \
                        cout << "parse: ent "                            \
                             << name_s                                   \
                             << " processing field "                     \
                             << it->first                                \
                             << " with value "                           \
                             << it->second                               \
                             << endl;                                    \
                        if (sscanf(it->second.c_str(), "%lf", &d) != 1) { \
                                cerr << "parse error reading ent field " \
                                     << it->first                        \
                                     << " == "                           \
                                     << it->second                       \
                                     << endl;                            \
                                exit(EX_DATAERR);                        \
                        }                                                \
                        ent-> FIELD = d;                                 \
                }
#else
        #define SET_ENT_FIELD_DOUBLE(FIELD)                              \
                it = fields.find(string( #FIELD ));                      \
                if (it != fields.end()) {                                \
                        if (sscanf(it->second.c_str(), "%lf", &d) != 1) { \
                                cerr << "parse error reading ent field " \
                                     << it->first                        \
                                     << " == "                           \
                                     << it->second                       \
                                     << endl;                            \
                                exit(EX_DATAERR);                        \
                        }                                                \
                        ent-> FIELD = d;                                 \
                }
#endif

#define SET_CHARACTER()                            \
        Mobile *character;                         \
        it_entses = entses.find(it_e->first);      \
        if (it_entses == entses.end()) {           \
                cerr << "parse error making ent '" \
                     << it_e->first                \
                     << "' behavior '"             \
                     << it_b->first                \
                     << "': ent '"                 \
                     << it_e->first                \
                     << "' not found"              \
                     << endl;                      \
                exit(EX_SOFTWARE);                 \
        }                                          \
        character = it_entses->second;

#define SET_TARGET()                                               \
        Mobile *target;                                            \
        it_fields = it_b->second->find(string("target"));          \
        if (it_fields == it_b->second->end()) {                    \
                cerr << "parse error making ent '"                 \
                     << it_e->first                                \
                     << "' behavior '"                             \
                     << it_b->first                                \
                     << "': required field 'target' not specified" \
                     << endl;                                      \
                exit(EX_DATAERR);                                  \
        }                                                          \
        it_entses = entses.find(it_fields->second);                \
        if (it_entses == entses.end()) {                           \
                cerr << "parse error making ent '"                 \
                     << it_e->first                                \
                     << "' behavior '"                             \
                     << it_b->first                                \
                     << "': field 'target' == '"                   \
                     << it_fields->second                          \
                     << "': ent not found"                         \
                     << endl;                                      \
                exit(EX_DATAERR);                                  \
        }                                                          \
        target = it_entses->second;

#define SET_DOUBLE(FIELD)                                              \
        double FIELD ;                                                 \
        it_fields = it_b->second->find(string( #FIELD ));              \
        if (it_fields == it_b->second->end()) {                        \
                cerr << "parse error making ent '"                     \
                     << it_e->first                                    \
                     << "' behavior '"                                 \
                     << it_b->first                                    \
                     << "': required field '" #FIELD "' not specified" \
                     << endl;                                          \
                exit(EX_DATAERR);                                      \
        }                                                              \
        if (sscanf(it_fields->second.c_str(), "%lf", & FIELD ) != 1) { \
                cerr << "parse error making ent '"                     \
                     << it_e->first                                    \
                     << "' behavior '"                                 \
                     << it_b->first                                    \
                     << "': required field '" #FIELD "' == '"          \
                     << it_fields->second                              \
                     << "' not a floating-point number"                \
                     << endl;                                          \
                exit(EX_DATAERR);                                      \
        }

#define SET_P()                                        \
        p = dynamic_cast<RuntimePekomin *>(character); \
        if (p == NULL) {                               \
                cerr << "parse error making ent '"     \
                     << it_e->first                    \
                     << "' behavior '"                 \
                     << it_b->first                    \
                     << "': ent '"                     \
                     << it_e->first                    \
                     << "' is not RuntimePekomin"      \
                     << endl;                          \
                exit(EX_SOFTWARE);                     \
        }

using namespace std;

unordered_map<string, Mobile *> entses;
unordered_map<string, unordered_map<string, unordered_map<string, string> *> *> behaviorses;

void parse_r(char *s, int chars) {
        double d;
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
        cout << "parse: entering ent " << name_s << endl;
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
                        cout << "parse: leaving ent " << name_s << endl;
#endif

        it = fields.find(string("class"));
        if (it == fields.end()) {
                cerr << "parse error reading ent " << name_s << ": class attribute not specified" << endl;
                exit(EX_DATAERR);
        } else {
                if (it->second == string("Player")) {
                        if (player != NULL) {
                                cerr << "parse error: player already defined" << endl;
                                exit(EX_DATAERR);
                        }
                        ent = player = new Player();
                }
                else if (it->second == string("Phantom"       )) ent = new Phantom()       ;
                else if (it->second == string("RuntimePekomin")) ent = new RuntimePekomin();

                ents.push_back(ent);
        }

        SET_ENT_FIELD_DOUBLE(pos.x);
        SET_ENT_FIELD_DOUBLE(pos.y);
        SET_ENT_FIELD_DOUBLE(pos.z);
        SET_ENT_FIELD_DOUBLE(ang  );
        SET_ENT_FIELD_DOUBLE(vel.x);
        SET_ENT_FIELD_DOUBLE(vel.y);
        SET_ENT_FIELD_DOUBLE(vel.z);
        SET_ENT_FIELD_DOUBLE(vrot );

        entses[name_s]      = ent      ;
        behaviorses[name_s] = behaviors;

        fields.erase(fields.begin(), fields.end());

#ifdef DEBUG_PARSE
        cout << endl;
#endif

        parse_r(s, chars);
}

void parse(char *s) {
        string class_s;
        unordered_map<string, string                                                  >::const_iterator it_fields;
        unordered_map<string, Mobile *                                                >::const_iterator it_entses;
        unordered_map<string, unordered_map<string, unordered_map<string, string> *> *>::const_iterator it_e;
                              unordered_map<string, unordered_map<string, string> *>   ::const_iterator it_b;
        RuntimePekomin *p;

        parse_r(s, 0);

        for (it_e = behaviorses.begin(); it_e != behaviorses.end(); ++it_e) {
                if (it_e->first == "player") continue;
                for (it_b = it_e->second->begin(); it_b != it_e->second->end(); ++it_b) {
#ifdef DEBUG_PARSE
                        cout << "parse: making behavior: " << it_b->first << " for ent " << it_e->first << endl;
#endif

                        it_fields = it_b->second->find(string("class"));
                        if (it_fields != it_b->second->end()) {
                                class_s = it_fields->second;
                        } else {
                                cerr << "parse error making ent '" << it_e->first << "' behavior '" << it_b->first << "': required field 'class' not specified" << endl;
                                exit(EX_DATAERR);
                        }

                        // Align(Mobile *character, Mobile *target, double maxAngularVelocity, double targetRadius, double slowRadius);
                        if (class_s == string("Align")) {
                                SET_CHARACTER();
                                SET_TARGET();
                                SET_DOUBLE(maxAngularVelocity);
                                SET_DOUBLE(targetRadius      );
                                SET_DOUBLE(slowRadius        );

                                SET_P();
                                p->addBehavior(new Align(character, target, maxAngularVelocity, targetRadius, slowRadius));
                                continue;
                        }

                        // Arrive(Mobile *character, Mobile *target, double maxSpeed, double targetRadius, double slowRadius);
                        if (class_s == string("Arrive")) {
                                SET_CHARACTER();
                                SET_TARGET();
                                SET_DOUBLE(maxSpeed    );
                                SET_DOUBLE(targetRadius);
                                SET_DOUBLE(slowRadius  );

                                SET_P();
                                p->addBehavior(new Arrive(character, target, maxSpeed, targetRadius, slowRadius));
                                continue;
                        }

                        // Evade(Mobile *character, Mobile *target, double maxAcceleration);
                        if (class_s == string("Evade")) {
                                SET_CHARACTER();
                                SET_TARGET();
                                SET_DOUBLE(maxAcceleration);

                                SET_P();
                                p->addBehavior(new Evade(character, target, maxAcceleration));
                                continue;
                        }

                        // Face(Mobile *character, Mobile *target, double maxAngularVelocity, double targetRadius, double slowRadius);
                        if (class_s == string("Face")) {
                                SET_CHARACTER();
                                SET_TARGET();
                                SET_DOUBLE(maxAngularVelocity);
                                SET_DOUBLE(targetRadius);
                                SET_DOUBLE(slowRadius);

                                SET_P();
                                p->addBehavior(new Face(character, target, maxAngularVelocity, targetRadius, slowRadius));
                                continue;
                        }

                        // Flee(Mobile *character, Mobile *target, double maxSpeed, double fleeRadius);
                        if (class_s == string("Flee")) {
                                SET_CHARACTER();
                                SET_TARGET();
                                SET_DOUBLE(maxSpeed);
                                SET_DOUBLE(fleeRadius);

                                SET_P();
                                p->addBehavior(new Flee(character, target, maxSpeed, fleeRadius));
                                continue;
                        }

                        // KinematicArrive(Ent *character, Ent *target, double maxSpeed, double radius);
                        if (class_s == string("KinematicArrive")) {
                                SET_CHARACTER();
                                SET_TARGET();
                                SET_DOUBLE(maxSpeed);
                                SET_DOUBLE(radius);

                                SET_P();
                                p->addBehavior(new KinematicArrive(character, target, maxSpeed, radius));
                                continue;
                        }

                        // KinematicFlee(Ent *character, Ent *target, double maxSpeed);
                        if (class_s == string("KinematicFlee")) {
                                SET_CHARACTER();
                                SET_TARGET();
                                SET_DOUBLE(maxSpeed);

                                SET_P();
                                p->addBehavior(new KinematicFlee(character, target, maxSpeed));
                                continue;
                        }

                        // KinematicSeek(Ent *character, Ent *target, double maxSpeed);
                        if (class_s == string("KinematicSeek")) {
                                SET_CHARACTER();
                                SET_TARGET();
                                SET_DOUBLE(maxSpeed);

                                SET_P();
                                p->addBehavior(new KinematicSeek(character, target, maxSpeed));
                                continue;
                        }

                        // KinematicWander(Ent *character, double maxSpeed, double maxRotation);
                        if (class_s == string("KinematicWander")) {
                                SET_CHARACTER();
                                SET_DOUBLE(maxSpeed);
                                SET_DOUBLE(maxRotation);

                                SET_P();
                                p->addBehavior(new KinematicWander(character, maxSpeed, maxRotation));
                                continue;
                        }

                        // LookWhereYoureGoing(Mobile *character, double maxAngularVelocity, double targetRadius, double slowRadius);
                        if (class_s == string("LookWhereYoureGoing")) {
                                SET_CHARACTER();
                                SET_DOUBLE(maxAngularVelocity);
                                SET_DOUBLE(targetRadius);
                                SET_DOUBLE(slowRadius);

                                SET_P();
                                p->addBehavior(new LookWhereYoureGoing(character, maxAngularVelocity, targetRadius, slowRadius));
                                continue;
                        }

                        // Pursue(Mobile *character, Mobile *target, double maxAcceleration);
                        if (class_s == string("Pursue")) {
                                SET_CHARACTER();
                                SET_TARGET();
                                SET_DOUBLE(maxAcceleration);

                                SET_P();
                                p->addBehavior(new Pursue(character, target, maxAcceleration));
                                continue;
                        }

                        // Seek(Mobile *character, Mobile *target, double maxAcceleration);
                        if (class_s == string("Seek")) {
                                SET_CHARACTER();
                                SET_TARGET();
                                SET_DOUBLE(maxAcceleration);

                                SET_P();
                                p->addBehavior(new Seek(character, target, maxAcceleration));
                                continue;
                        }

                        // Separation(Mobile *character, Mobile *target, double threshold, double decayCoefficient, double maxAcceleration);
                        if (class_s == string("Separation")) {
                                SET_CHARACTER();
                                SET_TARGET();
                                SET_DOUBLE(threshold);
                                SET_DOUBLE(decayCoefficient);
                                SET_DOUBLE(maxAcceleration);

                                SET_P();
                                p->addBehavior(new Separation(character, target, threshold, decayCoefficient, maxAcceleration));
                                continue;
                        }

                        // VelocityMatch(Mobile *character, Mobile *target, double maxAcceleration);
                        if (class_s == string("VelocityMatch")) {
                                SET_CHARACTER();
                                SET_TARGET();
                                SET_DOUBLE(maxAcceleration);

                                SET_P();
                                p->addBehavior(new VelocityMatch(character, target, maxAcceleration));
                                continue;
                        }

                        // Wander(Mobile *character, Mobile *target, double maxAngularAcceleration, double maxRotation, double targetRadius, double slowRadius, double wanderOffset, double wanderRadius, double wanderRate, double wanderTime, double maxAcceleration);
                        if (class_s == string("Wander")) {
                                SET_CHARACTER();
                                SET_DOUBLE(maxRotation);
                                SET_DOUBLE(targetRadius);
                                SET_DOUBLE(slowRadius);
                                SET_DOUBLE(wanderOffset);
                                SET_DOUBLE(wanderRadius);
                                SET_DOUBLE(wanderRate);
                                SET_DOUBLE(wanderTime);
                                SET_DOUBLE(maxAcceleration);

                                SET_P();
                                p->addBehavior(new Wander(character, maxRotation, targetRadius, slowRadius, wanderOffset, wanderRadius, wanderRate, wanderTime, maxAcceleration));
                                continue;
                        }

                        cerr << "parse error making ent '" << it_e->first << "' behavior '" << it_b->first << "': field 'class' == '" << it_fields->second << "': class not found" << endl;
                        exit(EX_DATAERR);
                }
        }

        // TODO: DELETE HEAP GARBAGE: delete behaviorses and entses.
}

