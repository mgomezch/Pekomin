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
#include "RuntimePoint.hpp"
#include "RuntimeSegment.hpp"
#include "RuntimeBox.hpp"

#define DEBUG_PARSE

#ifdef DEBUG_PARSE
        #define SET_ENT_FIELD_STRING(FIELD)                 \
                it = fields.find(string( #FIELD ));         \
                if (it != fields.end()) {                   \
                        cout << "parse: Ent "               \
                             << name_s                      \
                             << " processing string field " \
                             << it->first                   \
                             << " with value \""            \
                             << it->second                  \
                             << "\""                        \
                             << endl;                       \
                        ent-> FIELD = it->second;           \
                }
        #define SET_ENT_FIELD_STRING_D(FIELD, DEFAULT)      \
                SET_ENT_FIELD_STRING(FIELD)                 \
                else ent-> FIELD = DEFAULT;                 \
                cout << "parse: Ent "                       \
                     << name_s                              \
                     << " processing string field "         \
                     << it->first                           \
                     << " with default value \""            \
                     << DEFAULT                             \
                     << "\""                                \
                     << endl;
#else
        #define SET_ENT_FIELD_STRING(FIELD)                 \
                it = fields.find(string( #FIELD ));         \
                if (it != fields.end()) {                   \
                        ent-> FIELD = it->second;           \
                }
        #define SET_ENT_FIELD_STRING_D(FIELD, DEFAULT)      \
                SET_ENT_FIELD_STRING(FIELD)                 \
                else ent-> FIELD = DEFAULT;
#endif

#ifdef DEBUG_PARSE
        #define SET_ENT_FIELD_DOUBLE(FIELD)                                     \
                it = fields.find(string( #FIELD ));                             \
                if (it != fields.end()) {                                       \
                        cout << "parse: Ent "                                   \
                             << name_s                                          \
                             << " processing string field "                     \
                             << it->first                                       \
                             << " with value \""                                \
                             << it->second                                      \
                             << "\""                                            \
                             << endl;                                           \
                        if (sscanf(it->second.c_str(), "%lf", &d) != 1) {       \
                                cerr << "parse error reading Ent double field " \
                                     << it->first                               \
                                     << " == "                                  \
                                     << it->second                              \
                                     << endl;                                   \
                                exit(EX_DATAERR);                               \
                        }                                                       \
                        ent-> FIELD = d;                                        \
                }
        #define SET_ENT_FIELD_DOUBLE_D(FIELD, DEFAULT)                          \
                SET_ENT_FIELD_DOUBLE(FIELD)                                     \
                else ent-> FIELD = DEFAULT;                                     \
                cout << "parse: Ent "                                           \
                     << name_s                                                  \
                     << " processing string field "                             \
                     << it->first                                               \
                     << " with default value \""                                \
                     << DEFAULT                                                 \
                     << "\""                                                    \
                     << endl;
#else
        #define SET_ENT_FIELD_DOUBLE(FIELD)                                     \
                it = fields.find(string( #FIELD ));                             \
                if (it != fields.end()) {                                       \
                        if (sscanf(it->second.c_str(), "%lf", &d) != 1) {       \
                                cerr << "parse error reading Ent double field " \
                                     << it->first                               \
                                     << " == "                                  \
                                     << it->second                              \
                                     << endl;                                   \
                                exit(EX_DATAERR);                               \
                        }                                                       \
                        ent-> FIELD = d;                                        \
                }
        #define SET_ENT_FIELD_DOUBLE_D(FIELD, DEFAULT)                          \
                SET_ENT_FIELD_DOUBLE(FIELD)                                     \
                else ent-> FIELD = DEFAULT;
#endif

#ifdef DEBUG_PARSE
        #define SET_SEGMENT_FIELD_DOUBLE(FIELD)                                     \
                it = fields.find(string( #FIELD ));                                 \
                if (it != fields.end()) {                                           \
                        cout << "parse: Ent "                                       \
                             << name_s                                              \
                             << " processing Segment double field "                 \
                             << it->first                                           \
                             << " with value "                                      \
                             << it->second                                          \
                             << endl;                                               \
                        if (sscanf(it->second.c_str(), "%lf", &d) != 1) {           \
                                cerr << "parse error reading Segment double field " \
                                     << it->first                                   \
                                     << " == "                                      \
                                     << it->second                                  \
                                     << endl;                                       \
                                exit(EX_DATAERR);                                   \
                        }                                                           \
                        rs-> FIELD = d;                                             \
                }
        #define SET_SEGMENT_FIELD_DOUBLE_D(FIELD, DEFAULT)                          \
                SET_SEGMENT_FIELD_DOUBLE(FIELD)                                     \
                else rs-> FIELD = DEFAULT;                                          \
                cout << "parse: Ent "                                               \
                     << name_s                                                      \
                     << " processing Segment double field "                         \
                     << it->first                                                   \
                     << " with default value "                                      \
                     << DEFAULT                                                     \
                     << endl;
#else
        #define SET_SEGMENT_FIELD_DOUBLE(FIELD)                                     \
                it = fields.find(string( #FIELD ));                                 \
                if (it != fields.end()) {                                           \
                        if (sscanf(it->second.c_str(), "%lf", &d) != 1) {           \
                                cerr << "parse error reading Segment double field " \
                                     << it->first                                   \
                                     << " == "                                      \
                                     << it->second                                  \
                                     << endl;                                       \
                                exit(EX_DATAERR);                                   \
                        }                                                           \
                        rs-> FIELD = d;                                             \
                }
        #define SET_SEGMENT_FIELD_DOUBLE_D(FIELD, DEFAULT)                          \
                SET_SEGMENT_FIELD_DOUBLE(FIELD)                                     \
                else rs-> FIELD = DEFAULT;
#endif

#ifdef DEBUG_PARSE
#       define SET_BOX_FIELD_DOUBLE(FIELD)                                      \
                it = fields.find(string( #FIELD ));                             \
                if (it != fields.end()) {                                       \
                        cout << "parse: Ent "                                   \
                             << name_s                                          \
                             << " processing Box double field "                 \
                             << it->first                                       \
                             << " with value "                                  \
                             << it->second                                      \
                             << endl;                                           \
                        if (sscanf(it->second.c_str(), "%lf", &d) != 1) {       \
                                cerr << "parse error reading Box double field " \
                                     << it->first                               \
                                     << " == "                                  \
                                     << it->second                              \
                                     << endl;                                   \
                                exit(EX_DATAERR);                               \
                        }                                                       \
                        rb-> FIELD = d;                                         \
                }
#       define SET_BOX_FIELD_DOUBLE_D(FIELD, DEFAULT)                           \
                SET_BOX_FIELD_DOUBLE(FIELD)                                     \
                else rb-> FIELD = DEFAULT;                                      \
                cout << "parse: Ent "                                           \
                     << name_s                                                  \
                     << " processing Box double field "                         \
                     << it->first                                               \
                     << " with default value "                                  \
                     << DEFAULT                                                 \
                     << endl;
#else
#       define SET_BOX_FIELD_DOUBLE(FIELD)                                      \
                it = fields.find(string( #FIELD ));                             \
                if (it != fields.end()) {                                       \
                        if (sscanf(it->second.c_str(), "%lf", &d) != 1) {       \
                                cerr << "parse error reading Box double field " \
                                     << it->first                               \
                                     << " == "                                  \
                                     << it->second                              \
                                     << endl;                                   \
                                exit(EX_DATAERR);                               \
                        }                                                       \
                        rb-> FIELD = d;                                         \
                }
#       define SET_BOX_FIELD_DOUBLE_D(FIELD, DEFAULT)                           \
                SET_BOX_FIELD_DOUBLE(FIELD)                                     \
                else rb-> FIELD = DEFAULT;
#endif

#define SET_CHARACTER()                            \
        Mobile *character;                         \
        it_entses = entses.find(it_e->first);      \
        if (it_entses == entses.end()) {           \
                cerr << "parse error making Ent '" \
                     << it_e->first                \
                     << "' behavior '"             \
                     << it_b->first                \
                     << "': Ent '"                 \
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
                cerr << "parse error making Ent '"                 \
                     << it_e->first                                \
                     << "' behavior '"                             \
                     << it_b->first                                \
                     << "': required field 'target' not specified" \
                     << endl;                                      \
                exit(EX_DATAERR);                                  \
        }                                                          \
        it_entses = entses.find(it_fields->second);                \
        if (it_entses == entses.end()) {                           \
                cerr << "parse error making Ent '"                 \
                     << it_e->first                                \
                     << "' behavior '"                             \
                     << it_b->first                                \
                     << "': field 'target' == '"                   \
                     << it_fields->second                          \
                     << "': Ent not found"                         \
                     << endl;                                      \
                exit(EX_DATAERR);                                  \
        }                                                          \
        target = it_entses->second;

#ifdef DEBUG_PARSE
#       define SET_DOUBLE_D(FIELD, DEFAULT)                                                 \
                double FIELD ;                                                              \
                it_fields = it_b->second->find(string( #FIELD ));                           \
                if (it_fields == it_b->second->end()) {                                     \
                        cout << "parse: Ent '"                                              \
                             << it_e->first                                                 \
                             << "' behavior '"                                              \
                             << it_b->first                                                 \
                             << "': processing double field " #FIELD " with default value " \
                             << DEFAULT                                                     \
                             << endl;                                                       \
                        FIELD = DEFAULT;                                                    \
                }                                                                           \
                if (sscanf(it_fields->second.c_str(), "%lf", & FIELD ) != 1) {              \
                        cerr << "parse error making Ent '"                                  \
                             << it_e->first                                                 \
                             << "' behavior '"                                              \
                             << it_b->first                                                 \
                             << "': specified field '" #FIELD "' == '"                      \
                             << it_fields->second                                           \
                             << "' not a floating-point number"                             \
                             << endl;                                                       \
                        exit(EX_DATAERR);                                                   \
                }
#       define SET_DOUBLE(FIELD)                                               \
                double FIELD ;                                                 \
                it_fields = it_b->second->find(string( #FIELD ));              \
                if (it_fields == it_b->second->end()) {                        \
                        cerr << "parse error making Ent '"                     \
                             << it_e->first                                    \
                             << "' behavior '"                                 \
                             << it_b->first                                    \
                             << "': required field '" #FIELD "' not specified" \
                             << endl;                                          \
                        exit(EX_DATAERR);                                      \
                }                                                              \
                if (sscanf(it_fields->second.c_str(), "%lf", & FIELD ) != 1) { \
                        cerr << "parse error making Ent '"                     \
                             << it_e->first                                    \
                             << "' behavior '"                                 \
                             << it_b->first                                    \
                             << "': specified field '" #FIELD "' == '"         \
                             << it_fields->second                              \
                             << "' not a floating-point number"                \
                             << endl;                                          \
                        exit(EX_DATAERR);                                      \
                }                                                              \
                cout << "parse: Ent '"                                         \
                     << it_e->first                                            \
                     << "' behavior '"                                         \
                     << it_b->first                                            \
                     << "': processing double field " #FIELD " with value "    \
                     << FIELD                                                  \
                     << endl;
#else
#       define SET_DOUBLE_D(FIELD, DEFAULT)                                    \
                double FIELD ;                                                 \
                it_fields = it_b->second->find(string( #FIELD ));              \
                if (it_fields == it_b->second->end()) {                        \
                        FIELD = DEFAULT;                                       \
                }                                                              \
                if (sscanf(it_fields->second.c_str(), "%lf", & FIELD ) != 1) { \
                        cerr << "parse error making Ent '"                     \
                             << it_e->first                                    \
                             << "' behavior '"                                 \
                             << it_b->first                                    \
                             << "': specified field '" #FIELD "' == '"         \
                             << it_fields->second                              \
                             << "' not a floating-point number"                \
                             << endl;                                          \
                        exit(EX_DATAERR);                                      \
                }
#       define SET_DOUBLE(FIELD)                                               \
                double FIELD ;                                                 \
                it_fields = it_b->second->find(string( #FIELD ));              \
                if (it_fields == it_b->second->end()) {                        \
                        cerr << "parse error making Ent '"                     \
                             << it_e->first                                    \
                             << "' behavior '"                                 \
                             << it_b->first                                    \
                             << "': required field '" #FIELD "' not specified" \
                             << endl;                                          \
                        exit(EX_DATAERR);                                      \
                }                                                              \
                if (sscanf(it_fields->second.c_str(), "%lf", & FIELD ) != 1) { \
                        cerr << "parse error making Ent '"                     \
                             << it_e->first                                    \
                             << "' behavior '"                                 \
                             << it_b->first                                    \
                             << "': specified field '" #FIELD "' == '"         \
                             << it_fields->second                              \
                             << "' not a floating-point number"                \
                             << endl;                                          \
                        exit(EX_DATAERR);                                      \
                }
#endif

#define SET_P(BEHAVIOR)                              \
        p = dynamic_cast<RuntimePoint *>(character); \
        if (p != NULL) p->addBehavior(BEHAVIOR);     \
        else {                                       \
                cerr << "parse error making Ent '"   \
                     << it_e->first                  \
                     << "' behavior '"               \
                     << it_b->first                  \
                     << "': Ent '"                   \
                     << it_e->first                  \
                     << "' is not a RuntimePoint"    \
                     << endl;                        \
                exit(EX_SOFTWARE);                   \
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
        cout << "parse: read Ent name " << name_s << endl;
#endif
        name_s = string(name);
        free(name);

        nextchars = -1;
        switch(sscanf(s + chars, " { %n", &nextchars)) {
                case 0:
                case EOF:
                        if (nextchars == -1) {
                                cerr << "parse error reading Ent " << name_s << ": expected '{'" << endl;
                                exit(EX_DATAERR);
                        }
                default:
                        chars += nextchars;
        }
#ifdef DEBUG_PARSE
        cout << "parse: entering Ent " << name_s << endl;
#endif

        while (nextchars = -1, sscanf(s + chars, " } %n", &nextchars), nextchars == -1) {
                // Field
                field = value = NULL;
                if (sscanf(s + chars, " %m[a-zA-Z_0-9.] = %m[a-zA-Z_0-9.-] ;%n", &field, &value, &nextchars) >= 2) {
                        chars += nextchars;
                        field_s = string(field);
                        free(field);
                        value_s = string(value);
                        free(value);
#ifdef DEBUG_PARSE
                        cout << "        parse: Ent " << name_s << ": found field: " << field_s << " = " << value_s << endl;
#endif
                        fields[field_s] = value_s;
                }

                // Behavior
                else if (sscanf(s + chars, " %ms { %n", &type, &nextchars) >= 1) {
                        chars += nextchars;
                        type_s = string(type);
                        free(type);
#ifdef DEBUG_PARSE
                        cout << "        parse: Ent " << name_s << ": found behavior: " << type_s << "; entering" << endl;
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
                                        cout << "                parse: Ent " << name_s << ": behavior " << type_s << ": found field: " << field_s << " = " << value_s << endl;
#endif
                                } else {
                                        cerr << "parse error reading Ent " << name_s << ", behavior " << type_s << ": expected field or '}'" << endl;
                                        exit(EX_DATAERR);
                                }
                        }
                        chars += nextchars;
#ifdef DEBUG_PARSE
                        cout << "        parse: Ent " << name_s << ": leaving behavior " << type_s << endl;
#endif
                }

                // Error
                else {
                        cerr << "parse error reading Ent " << name_s << ": expected field, behavior or '}'" << endl;
                        exit(EX_DATAERR);
                }
        }
        chars += nextchars;
#ifdef DEBUG_PARSE
        cout << "parse: leaving Ent " << name_s << endl;
#endif

        it = fields.find(string("class"));
        if (it == fields.end()) {
                cerr << "parse error reading Ent " << name_s << ": class attribute not specified" << endl;
                exit(EX_DATAERR);
        } else {
                if (it->second == string("Player")) {
                        if (player != NULL) {
                                cerr << "parse error: player already defined" << endl;
                                exit(EX_DATAERR);
                        }
                        ent = player = new Player();
                }
                else if (it->second == string("Phantom"       )) ent = new Phantom();
                else if (it->second == string("RuntimePoint"  )) ent = new RuntimePoint();
                else if (it->second == string("RuntimeSegment")) {
                        RuntimeSegment *rs = new RuntimeSegment();

                        SET_SEGMENT_FIELD_DOUBLE(p1.x);
                        SET_SEGMENT_FIELD_DOUBLE(p1.y);
                        SET_SEGMENT_FIELD_DOUBLE(p1.z);
                        SET_SEGMENT_FIELD_DOUBLE(p2.x);
                        SET_SEGMENT_FIELD_DOUBLE(p2.y);
                        SET_SEGMENT_FIELD_DOUBLE(p2.z);

                        ent = rs;
                } else if (it->second == string("RuntimeBox")) {
                        RuntimeBox *rb = new RuntimeBox();

                        SET_BOX_FIELD_DOUBLE(sx);
                        SET_BOX_FIELD_DOUBLE(sy);
                        SET_BOX_FIELD_DOUBLE(sz);

                        ent = rb;
                } else {
                        cerr << "parse error reading Ent " << name_s << ": unknown class " << it->second << endl;
                        exit(EX_DATAERR);
                }

                ents.push_back(ent);
        }

        ent->name = name_s;

        SET_ENT_FIELD_DOUBLE(pos.x);
        SET_ENT_FIELD_DOUBLE(pos.y);
        SET_ENT_FIELD_DOUBLE(pos.z);
        SET_ENT_FIELD_DOUBLE(ang  );
        SET_ENT_FIELD_DOUBLE(vel.x);
        SET_ENT_FIELD_DOUBLE(vel.y);
        SET_ENT_FIELD_DOUBLE(vel.z);
        SET_ENT_FIELD_DOUBLE(vrot );

        entses[name_s] = ent;
        behaviorses[name_s] = behaviors;

        fields.erase(fields.begin(), fields.end());

#ifdef DEBUG_PARSE
        cout << endl;
#endif

        parse_r(s, chars);
}

void parse(char *s) {
        string class_s;
        unordered_map<string, string  >::const_iterator it_fields;
        unordered_map<string, Mobile *>::const_iterator it_entses;
        RuntimePoint *p;

        parse_r(s, 0);

        for (auto it_e = behaviorses.begin(); it_e != behaviorses.end(); ++it_e) {
                for (auto it_b = it_e->second->begin(); it_b != it_e->second->end(); ++it_b) {
#ifdef DEBUG_PARSE
                        cout << "parse: making behavior: " << it_b->first << " for Ent " << it_e->first << endl;
#endif

                        it_fields = it_b->second->find(string("class"));
                        if (it_fields != it_b->second->end()) {
                                class_s = it_fields->second;
                        } else {
                                cerr << "parse error making Ent '" << it_e->first << "' behavior '" << it_b->first << "': required field 'class' not specified" << endl;
                                exit(EX_DATAERR);
                        }

                        // Align(Mobile *character, Mobile *target, double maxAngularVelocity, double targetRadius, double slowRadius);
                        if (class_s == string("Align")) {
                                SET_CHARACTER();
                                SET_TARGET();
                                SET_DOUBLE(maxAngularVelocity);
                                SET_DOUBLE(targetRadius      );
                                SET_DOUBLE(slowRadius        );

                                SET_P(new Align(character, target, maxAngularVelocity, targetRadius, slowRadius));
                                continue;
                        }

                        // Arrive(Mobile *character, Mobile *target, double maxSpeed, double targetRadius, double slowRadius);
                        if (class_s == string("Arrive")) {
                                SET_CHARACTER();
                                SET_TARGET();
                                SET_DOUBLE(maxSpeed    );
                                SET_DOUBLE(targetRadius);
                                SET_DOUBLE(slowRadius  );

                                SET_P(new Arrive(character, target, maxSpeed, targetRadius, slowRadius));
                                continue;
                        }

                        // BoundedDynamicSeparation(Mobile *character, Mobile *target, double maxForce, double separationRadius);
                        if (class_s == string("BoundedDynamicSeparation")) {
                                SET_CHARACTER();
                                SET_TARGET();
                                SET_DOUBLE(maxForce);
                                SET_DOUBLE(separationRadius);

                                SET_P(new BoundedDynamicSeparation(character, target, maxForce, separationRadius));
                                continue;
                        }

                        // DynamicSeparation(Mobile *character, Mobile *target, double minForce, double separationRadius);
                        if (class_s == string("DynamicSeparation")) {
                                SET_CHARACTER();
                                SET_TARGET();
                                SET_DOUBLE(minForce);
                                SET_DOUBLE(separationRadius);

                                SET_P(new DynamicSeparation(character, target, minForce, separationRadius));
                                continue;
                        }

                        // Evade(Mobile *character, Mobile *target, double maxAcceleration);
                        if (class_s == string("Evade")) {
                                SET_CHARACTER();
                                SET_TARGET();
                                SET_DOUBLE(maxSpeed);

                                SET_P(new Evade(character, target, maxSpeed));
                                continue;
                        }

                        // Face(Mobile *character, Mobile *target, double maxAngularVelocity, double targetRadius, double slowRadius);
                        if (class_s == string("Face")) {
                                SET_CHARACTER();
                                SET_TARGET();
                                SET_DOUBLE(maxAngularVelocity);
                                SET_DOUBLE(targetRadius);
                                SET_DOUBLE(slowRadius);

                                SET_P(new Face(character, target, maxAngularVelocity, targetRadius, slowRadius));
                                continue;
                        }

                        // Separation(Mobile *character, Mobile *target, double maxSpeed, double separationRadius);
                        if (class_s == string("Separation")) {
                                SET_CHARACTER();
                                SET_TARGET();
                                SET_DOUBLE(maxSpeed);
                                SET_DOUBLE(separationRadius);

                                SET_P(new Separation(character, target, maxSpeed, separationRadius));
                                continue;
                        }

                        // KinematicArrive(Ent *character, Ent *target, double maxSpeed, double radius);
                        if (class_s == string("KinematicArrive")) {
                                SET_CHARACTER();
                                SET_TARGET();
                                SET_DOUBLE(maxSpeed);
                                SET_DOUBLE(radius);

                                SET_P(new KinematicArrive(character, target, maxSpeed, radius));
                                continue;
                        }

                        // KinematicSeparation(Ent *character, Ent *target, double maxSpeed, double separationRadius);
                        if (class_s == string("KinematicSeparation")) {
                                SET_CHARACTER();
                                SET_TARGET();
                                SET_DOUBLE(maxSpeed);
                                SET_DOUBLE(separationRadius);

                                SET_P(new KinematicSeparation(character, target, maxSpeed, separationRadius));
                                continue;
                        }

                        // KinematicSeek(Ent *character, Ent *target, double maxSpeed);
                        if (class_s == string("KinematicSeek")) {
                                SET_CHARACTER();
                                SET_TARGET();
                                SET_DOUBLE(maxSpeed);

                                SET_P(new KinematicSeek(character, target, maxSpeed));
                                continue;
                        }

                        // KinematicWander(Ent *character, double maxSpeed, double maxRotation, double wanderTime);
                        if (class_s == string("KinematicWander")) {
                                SET_CHARACTER();
                                SET_DOUBLE(maxSpeed);
                                SET_DOUBLE(maxRotation);
                                SET_DOUBLE(wanderTime);

                                SET_P(new KinematicWander(character, maxSpeed, maxRotation, wanderTime));
                                continue;
                        }

                        // StaticLookWhereYoureGoing(Mobile *character);
                        if (class_s == string("StaticLookWhereYoureGoing")) {
                                SET_CHARACTER();

                                SET_P(new StaticLookWhereYoureGoing(character));
                                continue;
                        }

                        // LookWhereYoureGoing(Mobile *character, double maxAngularVelocity, double targetRadius, double slowRadius);
                        if (class_s == string("LookWhereYoureGoing")) {
                                SET_CHARACTER();
                                SET_DOUBLE(maxAngularVelocity);
                                SET_DOUBLE(targetRadius);
                                SET_DOUBLE(slowRadius);

                                SET_P(new LookWhereYoureGoing(character, maxAngularVelocity, targetRadius, slowRadius));
                                continue;
                        }

                        // Pursue(Mobile *character, Mobile *target, double maxAcceleration);
                        if (class_s == string("Pursue")) {
                                SET_CHARACTER();
                                SET_TARGET();
                                SET_DOUBLE(maxSpeed);

                                SET_P(new Pursue(character, target, maxSpeed));
                                continue;
                        }

                        // Seek(Mobile *character, Mobile *target, double maxAcceleration);
                        if (class_s == string("Seek")) {
                                SET_CHARACTER();
                                SET_TARGET();
                                SET_DOUBLE(maxSpeed);

                                SET_P(new Seek(character, target, maxSpeed));
                                continue;
                        }

                        // StaticVelocityMatch(Mobile *character, Mobile *target);
                        if (class_s == string("StaticVelocityMatch")) {
                                SET_CHARACTER();
                                SET_TARGET();

                                SET_P(new StaticVelocityMatch(character, target));
                                continue;
                        }

                        // VelocityMatch(Mobile *character, Mobile *target, double maxAcceleration);
                        if (class_s == string("VelocityMatch")) {
                                SET_CHARACTER();
                                SET_TARGET();
                                SET_DOUBLE(maxAcceleration);

                                SET_P(new VelocityMatch(character, target, maxAcceleration));
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

                                SET_P(new Wander(character, maxRotation, targetRadius, slowRadius, wanderOffset, wanderRadius, wanderRate, wanderTime, maxAcceleration));
                                continue;
                        }

                        // PathFollowing(Mobile *character, Mobile *target, double maxSpeed, double targetRadius, double slowRadius);
                        if (class_s == string("PathFollowing")) {
                                SET_CHARACTER();
                                SET_TARGET();
                                SET_DOUBLE(maxSpeed);
                                SET_DOUBLE(targetRadius);
                                SET_DOUBLE(slowRadius);

                                SET_P(new PathFollowing(character, target, maxSpeed, targetRadius, slowRadius));
                                continue;
                        }

                        cerr << "parse error making Ent '" << it_e->first << "' behavior '" << it_b->first << "': field 'class' == '" << it_fields->second << "': class not found" << endl;
                        exit(EX_DATAERR);
                }
        }

        // TODO: DELETE HEAP GARBAGE: delete behaviorses and entses.
}
