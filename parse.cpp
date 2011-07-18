#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include <sysexits.h>

#include <SOLID/solid.h>

#include "Actor.hpp"
#include "Alien.hpp"
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
        #define SET_ENT_FIELD_STRING(FIELD)                      \
                it = fields.find(string( #FIELD ));              \
                if (it != fields.end()) {                        \
                        std::cout << "parse: Ent "               \
                                  << name_s                      \
                                  << " processing string field " \
                                  << it->first                   \
                                  << " with value \""            \
                                  << it->second                  \
                                  << "\""                        \
                                  << std::endl;                  \
                        ent-> FIELD = it->second;                \
                }
        #define SET_ENT_FIELD_STRING_D(FIELD, DEFAULT)                                          \
                SET_ENT_FIELD_STRING(FIELD)                                                     \
                else {                                                                          \
                        ent-> FIELD = DEFAULT;                                                  \
                        std::cout << "parse: Ent "                                              \
                                  << name_s                                                     \
                                  << " processing string field " #FIELD " with default value '" \
                                  << DEFAULT                                                    \
                                  << "'"                                                        \
                                  << std::endl;                                                 \
                }
#else
        #define SET_ENT_FIELD_STRING(FIELD)         \
                it = fields.find(string( #FIELD )); \
                if (it != fields.end()) {           \
                        ent-> FIELD = it->second;   \
                }
        #define SET_ENT_FIELD_STRING_D(FIELD, DEFAULT) \
                SET_ENT_FIELD_STRING(FIELD)            \
                else ent-> FIELD = DEFAULT;
#endif

#ifdef DEBUG_PARSE
        #define SET_ENT_FIELD_DOUBLE(FIELD)                                          \
                it = fields.find(string( #FIELD ));                                  \
                if (it != fields.end()) {                                            \
                        std::cout << "parse: Ent "                                   \
                                  << name_s                                          \
                                  << " processing double field "                     \
                                  << it->first                                       \
                                  << " with value '"                                 \
                                  << it->second                                      \
                                  << "'"                                             \
                                  << std::endl;                                      \
                        if (sscanf(it->second.c_str(), "%lf", &d) != 1) {            \
                                std::cerr << "parse error reading Ent double field " \
                                          << it->first                               \
                                          << " == "                                  \
                                          << it->second                              \
                                          << std::endl;                              \
                                exit(EX_DATAERR);                                    \
                        }                                                            \
                        ent-> FIELD = d;                                             \
                }
        #define SET_ENT_FIELD_DOUBLE_D(FIELD, DEFAULT)           \
                SET_ENT_FIELD_DOUBLE(FIELD)                      \
                else {                                           \
                        ent-> FIELD = DEFAULT;                   \
                        std::cout << "parse: Ent "                                              \
                                  << name_s                                                     \
                                  << " processing double field " #FIELD " with default value '" \
                                  << DEFAULT                                                    \
                                  << "'"                                                        \
                                  << std::endl;                                                 \
                }
#else
        #define SET_ENT_FIELD_DOUBLE(FIELD)                                          \
                it = fields.find(string( #FIELD ));                                  \
                if (it != fields.end()) {                                            \
                        if (sscanf(it->second.c_str(), "%lf", &d) != 1) {            \
                                std::cerr << "parse error reading Ent double field " \
                                          << it->first                               \
                                          << " == "                                  \
                                          << it->second                              \
                                          << std::endl;                              \
                                exit(EX_DATAERR);                                    \
                        }                                                            \
                        ent-> FIELD = d;                                             \
                }
        #define SET_ENT_FIELD_DOUBLE_D(FIELD, DEFAULT) \
                SET_ENT_FIELD_DOUBLE(FIELD)            \
                else ent-> FIELD = DEFAULT;
#endif

#ifdef DEBUG_PARSE
        #define SET_ENT_FIELD_BOOL(FIELD)                                          \
                it = fields.find(string( #FIELD ));                                \
                if (it != fields.end()) {                                          \
                        std::cout << "parse: Ent "                                 \
                                  << name_s                                        \
                                  << " processing bool field "                     \
                                  << it->first                                     \
                                  << " with value \""                              \
                                  << it->second                                    \
                                  << "\""                                          \
                                  << std::endl;                                    \
                        if      (it->second != "true" ) ent-> FIELD = true ;       \
                        else if (it->second != "false") ent-> FIELD = false;       \
                        else {                                                     \
                                std::cerr << "parse error reading Ent bool field " \
                                          << it->first                             \
                                          << " == "                                \
                                          << it->second                            \
                                          << std::endl;                            \
                                exit(EX_DATAERR);                                  \
                        }                                                          \
                }
        #define SET_ENT_FIELD_BOOL_D(FIELD, DEFAULT)                                           \
                SET_ENT_FIELD_BOOL(FIELD)                                                      \
                else {                                                                         \
                        ent-> FIELD = DEFAULT;                                                 \
                        std::cout << "parse: Ent "                                             \
                                  << name_s                                                    \
                                  << " processing bool field " #FIELD " with default value \'" \
                                  << DEFAULT                                                   \
                                  << "\'"                                                      \
                                  << std::endl;                                                \
                }
#else
        #define SET_ENT_FIELD_BOOL(FIELD)                                          \
                it = fields.find(string( #FIELD ));                                \
                if (it != fields.end()) {                                          \
                        if      (it->second != "true" ) ent-> FIELD = true ;       \
                        else if (it->second != "false") ent-> FIELD = false;       \
                        else {                                                     \
                                std::cerr << "parse error reading Ent bool field " \
                                          << it->first                             \
                                          << " == "                                \
                                          << it->second                            \
                                          << std::endl;                            \
                                exit(EX_DATAERR);                                  \
                        }                                                          \
                }
        #define SET_ENT_FIELD_BOOL_D(FIELD, DEFAULT) \
                SET_ENT_FIELD_BOOL(FIELD)            \
                else ent-> FIELD = DEFAULT;
#endif

#ifdef DEBUG_PARSE
        #define SET_SEGMENT_FIELD_DOUBLE(FIELD)                                          \
                it = fields.find(string( #FIELD ));                                      \
                if (it != fields.end()) {                                                \
                        std::cout << "parse: Ent "                                       \
                                  << name_s                                              \
                                  << " processing Segment double field "                 \
                                  << it->first                                           \
                                  << " with value "                                      \
                                  << it->second                                          \
                                  << std::endl;                                          \
                        if (sscanf(it->second.c_str(), "%lf", &d) != 1) {                \
                                std::cerr << "parse error reading Segment double field " \
                                          << it->first                                   \
                                          << " == "                                      \
                                          << it->second                                  \
                                          << std::endl;                                  \
                                exit(EX_DATAERR);                                        \
                        }                                                                \
                        rs-> FIELD = d;                                                  \
                }
        #define SET_SEGMENT_FIELD_DOUBLE_D(FIELD, DEFAULT)                                             \
                SET_SEGMENT_FIELD_DOUBLE(FIELD)                                                        \
                else {                                                                                 \
                        rs-> FIELD = DEFAULT;                                                          \
                        std::cout << "parse: Ent "                                                     \
                                  << name_s                                                            \
                                  << " processing Segment double field " #FIELD " with default value " \
                                  << DEFAULT                                                           \
                                  << std::endl;                                                        \
                }
#else
        #define SET_SEGMENT_FIELD_DOUBLE(FIELD)                                           \
                it = fields.find(string( #FIELD ));                                       \
                if (it != fields.end()) {                                                 \
                        if (sscanf(it->second.c_str(), "%lf", &d) != 1) {                 \
                                std::cerr << "parse error reading Segment double field '" \
                                          << it->first                                    \
                                          << "' == '"                                     \
                                          << it->second                                   \
                                          << "'"                                          \
                                          << std::endl;                                   \
                                exit(EX_DATAERR);                                         \
                        }                                                                 \
                        rs-> FIELD = d;                                                   \
                }
        #define SET_SEGMENT_FIELD_DOUBLE_D(FIELD, DEFAULT) \
                SET_SEGMENT_FIELD_DOUBLE(FIELD)            \
                else rs-> FIELD = DEFAULT;
#endif

#ifdef DEBUG_PARSE
#       define SET_BOX_FIELD_DOUBLE(FIELD)                                           \
                it = fields.find(string( #FIELD ));                                  \
                if (it != fields.end()) {                                            \
                        std::cout << "parse: Ent "                                   \
                                  << name_s                                          \
                                  << " processing Box double field "                 \
                                  << it->first                                       \
                                  << " with value "                                  \
                                  << it->second                                      \
                                  << std::endl;                                      \
                        if (sscanf(it->second.c_str(), "%lf", &d) != 1) {            \
                                std::cerr << "parse error reading Box double field " \
                                          << it->first                               \
                                          << " == "                                  \
                                          << it->second                              \
                                          << std::endl;                              \
                                exit(EX_DATAERR);                                    \
                        }                                                            \
                        rb-> FIELD = d;                                              \
                }
#       define SET_BOX_FIELD_DOUBLE_D(FIELD, DEFAULT)                                              \
                SET_BOX_FIELD_DOUBLE(FIELD)                                                        \
                else {                                                                             \
                        rb-> FIELD = DEFAULT;                                                      \
                        std::cout << "parse: Ent "                                                 \
                                  << name_s                                                        \
                                  << " processing Box double field " #FIELD " with default value " \
                                  << DEFAULT                                                       \
                                  << std::endl;                                                    \
                }
#else
#       define SET_BOX_FIELD_DOUBLE(FIELD)                                           \
                it = fields.find(string( #FIELD ));                                  \
                if (it != fields.end()) {                                            \
                        if (sscanf(it->second.c_str(), "%lf", &d) != 1) {            \
                                std::cerr << "parse error reading Box double field " \
                                          << it->first                               \
                                          << " == "                                  \
                                          << it->second                              \
                                          << std::endl;                              \
                                exit(EX_DATAERR);                                    \
                        }                                                            \
                        rb-> FIELD = d;                                              \
                }
#       define SET_BOX_FIELD_DOUBLE_D(FIELD, DEFAULT) \
                SET_BOX_FIELD_DOUBLE(FIELD)           \
                else rb-> FIELD = DEFAULT;
#endif

#define SET_BEHAVIOR_CHARACTER()                        \
        Mobile *character;                              \
        it_entses = entses.find(it_e->first);           \
        if (it_entses == entses.end()) {                \
                std::cerr << "parse error making Ent '" \
                          << it_e->first                \
                          << "' behavior '"             \
                          << it_b->first                \
                          << "': Ent '"                 \
                          << it_e->first                \
                          << "' not found"              \
                          << std::endl;                 \
                exit(EX_SOFTWARE);                      \
        }                                               \
        character = it_entses->second;

#define SET_BEHAVIOR_TARGET()                                           \
        Mobile *target;                                                 \
        it_fields = it_b->second->find(string("target"));               \
        if (it_fields == it_b->second->end()) {                         \
                std::cerr << "parse error making Ent '"                 \
                          << it_e->first                                \
                          << "' behavior '"                             \
                          << it_b->first                                \
                          << "': required field 'target' not specified" \
                          << std::endl;                                 \
                exit(EX_DATAERR);                                       \
        }                                                               \
        it_entses = entses.find(it_fields->second);                     \
        if (it_entses == entses.end()) {                                \
                std::cerr << "parse error making Ent '"                 \
                          << it_e->first                                \
                          << "' behavior '"                             \
                          << it_b->first                                \
                          << "': field 'target' == '"                   \
                          << it_fields->second                          \
                          << "': Ent not found"                         \
                          << std::endl;                                 \
                exit(EX_DATAERR);                                       \
        }                                                               \
        target = it_entses->second;

#ifdef DEBUG_PARSE
#       define SET_BEHAVIOR_BOOL_D(FIELD, DEFAULT)                                                \
                bool FIELD ;                                                                      \
                it_fields = it_b->second->find(string( #FIELD ));                                 \
                if (it_fields == it_b->second->end()) {                                           \
                        std::cout << "parse: Ent '"                                               \
                                  << it_e->first                                                  \
                                  << "' behavior '"                                               \
                                  << it_b->first                                                  \
                                  << "': processing bool field '" #FIELD "' with default value '" \
                                  << DEFAULT                                                      \
                                  << "'"                                                          \
                                  << std::endl;                                                   \
                        FIELD = DEFAULT;                                                          \
                }                                                                                 \
                if      (it_fields->second != "true" ) FIELD = true ;                             \
                else if (it_fields->second != "false") FIELD = false;                             \
                else {                                                                            \
                        std::cerr << "parse error making Ent '"                                   \
                                  << it_e->first                                                  \
                                  << "' behavior '"                                               \
                                  << it_b->first                                                  \
                                  << "': specified field '" #FIELD "' == '"                       \
                                  << it_fields->second                                            \
                                  << "' not a boolean"                                            \
                                  << std::endl;                                                   \
                        exit(EX_DATAERR);                                                         \
                }
#       define SET_BEHAVIOR_BOOL(FIELD)                                             \
                bool FIELD ;                                                        \
                it_fields = it_b->second->find(string( #FIELD ));                   \
                if (it_fields == it_b->second->end()) {                             \
                        std::cerr << "parse error making Ent '"                     \
                                  << it_e->first                                    \
                                  << "' behavior '"                                 \
                                  << it_b->first                                    \
                                  << "': required field '" #FIELD "' not specified" \
                                  << std::endl;                                     \
                        exit(EX_DATAERR);                                           \
                }                                                                   \
                if      (it_fields->second != "true" ) FIELD = true ;               \
                else if (it_fields->second != "false") FIELD = false;               \
                else {                                                              \
                        std::cerr << "parse error making Ent '"                     \
                                  << it_e->first                                    \
                                  << "' behavior '"                                 \
                                  << it_b->first                                    \
                                  << "': specified field '" #FIELD "' == '"         \
                                  << it_fields->second                              \
                                  << "' not a boolean"                              \
                                  << std::endl;                                     \
                        exit(EX_DATAERR);                                           \
                }                                                                   \
                std::cout << "parse: Ent '"                                         \
                          << it_e->first                                            \
                          << "' behavior '"                                         \
                          << it_b->first                                            \
                          << "': processing bool field " #FIELD " with value "      \
                          << FIELD                                                  \
                          << std::endl;
#else
#       define SET_BEHAVIOR_BOOL_D(FIELD, DEFAULT)                             \
                bool FIELD ;                                                   \
                it_fields = it_b->second->find(string( #FIELD ));              \
                if (it_fields == it_b->second->end()) {                        \
                        FIELD = DEFAULT;                                       \
                }                                                              \
                if      (it_fields->second != "true" ) FIELD = true ;          \
                else if (it_fields->second != "false") FIELD = false;          \
                else {                                                         \
                        std::cerr << "parse error making Ent '"                \
                                  << it_e->first                               \
                                  << "' behavior '"                            \
                                  << it_b->first                               \
                                  << "': specified field '" #FIELD "' == '"    \
                                  << it_fields->second                         \
                                  << "' not a boolean"                         \
                                  << std::endl;                                \
                        exit(EX_DATAERR);                                      \
                }
#       define SET_BEHAVIOR_BOOL(FIELD)                                             \
                bool FIELD ;                                                        \
                it_fields = it_b->second->find(string( #FIELD ));                   \
                if (it_fields == it_b->second->end()) {                             \
                        std::cerr << "parse error making Ent '"                     \
                                  << it_e->first                                    \
                                  << "' behavior '"                                 \
                                  << it_b->first                                    \
                                  << "': required field '" #FIELD "' not specified" \
                                  << std::endl;                                     \
                        exit(EX_DATAERR);                                           \
                }                                                                   \
                if      (it_fields->second != "true" ) FIELD = true ;               \
                else if (it_fields->second != "false") FIELD = false;               \
                else {                                                              \
                        std::cerr << "parse error making Ent '"                     \
                                  << it_e->first                                    \
                                  << "' behavior '"                                 \
                                  << it_b->first                                    \
                                  << "': specified field '" #FIELD "' == '"         \
                                  << it_fields->second                              \
                                  << "' not a boolean"                              \
                                  << std::endl;                                     \
                        exit(EX_DATAERR);                                           \
                }
#endif

#ifdef DEBUG_PARSE
#       define SET_BEHAVIOR_DOUBLE_D(FIELD, DEFAULT)                                                \
                double FIELD ;                                                                      \
                it_fields = it_b->second->find(string( #FIELD ));                                   \
                if (it_fields == it_b->second->end()) {                                             \
                        std::cout << "parse: Ent '"                                                 \
                                  << it_e->first                                                    \
                                  << "' behavior '"                                                 \
                                  << it_b->first                                                    \
                                  << "': processing double field '" #FIELD "' with default value '" \
                                  << DEFAULT                                                        \
                                  << "'"                                                            \
                                  << std::endl;                                                     \
                        FIELD = DEFAULT;                                                            \
                }                                                                                   \
                if (sscanf(it_fields->second.c_str(), "%lf", & FIELD ) != 1) {                      \
                        std::cerr << "parse error making Ent '"                                     \
                                  << it_e->first                                                    \
                                  << "' behavior '"                                                 \
                                  << it_b->first                                                    \
                                  << "': specified field '" #FIELD "' == '"                         \
                                  << it_fields->second                                              \
                                  << "' not a floating-point number"                                \
                                  << std::endl;                                                     \
                        exit(EX_DATAERR);                                                           \
                }
#       define SET_BEHAVIOR_DOUBLE(FIELD)                                           \
                double FIELD ;                                                      \
                it_fields = it_b->second->find(string( #FIELD ));                   \
                if (it_fields == it_b->second->end()) {                             \
                        std::cerr << "parse error making Ent '"                     \
                                  << it_e->first                                    \
                                  << "' behavior '"                                 \
                                  << it_b->first                                    \
                                  << "': required field '" #FIELD "' not specified" \
                                  << std::endl;                                     \
                        exit(EX_DATAERR);                                           \
                }                                                                   \
                if (sscanf(it_fields->second.c_str(), "%lf", & FIELD ) != 1) {      \
                        std::cerr << "parse error making Ent '"                     \
                                  << it_e->first                                    \
                                  << "' behavior '"                                 \
                                  << it_b->first                                    \
                                  << "': specified field '" #FIELD "' == '"         \
                                  << it_fields->second                              \
                                  << "' not a floating-point number"                \
                                  << std::endl;                                     \
                        exit(EX_DATAERR);                                           \
                }                                                                   \
                std::cout << "parse: Ent '"                                         \
                          << it_e->first                                            \
                          << "' behavior '"                                         \
                          << it_b->first                                            \
                          << "': processing double field " #FIELD " with value "    \
                          << FIELD                                                  \
                          << std::endl;
#else
#       define SET_BEHAVIOR_DOUBLE_D(FIELD, DEFAULT)                           \
                double FIELD ;                                                 \
                it_fields = it_b->second->find(string( #FIELD ));              \
                if (it_fields == it_b->second->end()) {                        \
                        FIELD = DEFAULT;                                       \
                }                                                              \
                if (sscanf(it_fields->second.c_str(), "%lf", & FIELD ) != 1) { \
                        std::cerr << "parse error making Ent '"                \
                                  << it_e->first                               \
                                  << "' behavior '"                            \
                                  << it_b->first                               \
                                  << "': specified field '" #FIELD "' == '"    \
                                  << it_fields->second                         \
                                  << "' not a floating-point number"           \
                                  << std::endl;                                \
                        exit(EX_DATAERR);                                      \
                }
#       define SET_BEHAVIOR_DOUBLE(FIELD)                                           \
                double FIELD ;                                                      \
                it_fields = it_b->second->find(string( #FIELD ));                   \
                if (it_fields == it_b->second->end()) {                             \
                        std::cerr << "parse error making Ent '"                     \
                                  << it_e->first                                    \
                                  << "' behavior '"                                 \
                                  << it_b->first                                    \
                                  << "': required field '" #FIELD "' not specified" \
                                  << std::endl;                                     \
                        exit(EX_DATAERR);                                           \
                }                                                                   \
                if (sscanf(it_fields->second.c_str(), "%lf", & FIELD ) != 1) {      \
                        std::cerr << "parse error making Ent '"                     \
                                  << it_e->first                                    \
                                  << "' behavior '"                                 \
                                  << it_b->first                                    \
                                  << "': specified field '" #FIELD "' == '"         \
                                  << it_fields->second                              \
                                  << "' not a floating-point number"                \
                                  << std::endl;                                     \
                        exit(EX_DATAERR);                                           \
                }
#endif

#define SET_P(BEHAVIOR)                                 \
        p = dynamic_cast<Actor *>(character);           \
        if (p != NULL) p->addBehavior(BEHAVIOR);        \
        else {                                          \
                std::cerr << "parse error making Ent '" \
                          << it_e->first                \
                          << "' behavior '"             \
                          << it_b->first                \
                          << "': Ent '"                 \
                          << it_e->first                \
                          << "' is not an Actor"        \
                          << std::endl;                 \
                exit(EX_SOFTWARE);                      \
        }

using std::unordered_map;
using std::string;

unordered_map<string, Mobile *> entses;
unordered_map<string, unordered_map<string, unordered_map<string, string> *> *> behaviorses;

void parse_r(char *s, int chars) {
        double d;
        char   *name  , *type  , *field  , *value  ;
        string  name_s,  type_s,  field_s,  value_s, ent_class;
        auto fields = unordered_map<string, string>();
        auto behaviors = new unordered_map<string, unordered_map<string, string> *>();
        int nextchars;
        Mobile *ent;

#ifdef DEBUG_PARSE
        std::cout << "parse: starting at " << static_cast<void *>(s) << " + " << chars << std::endl;
#endif

        switch (sscanf(s + chars, " %ms %n", &name, &nextchars)) {
                case 0:
                        std::cerr << "parse error reading name" << std::endl;
                        exit(EX_DATAERR);
                case EOF:
                        return;
                default:
                        chars += nextchars;
        }
#ifdef DEBUG_PARSE
        std::cout << "parse: read Ent name " << name_s << std::endl;
#endif
        name_s = string(name);
        free(name);

        nextchars = -1;
        switch(sscanf(s + chars, " { %n", &nextchars)) {
                case 0:
                case EOF:
                        if (nextchars == -1) {
                                std::cerr << "parse error reading Ent " << name_s << ": expected '{'" << std::endl;
                                exit(EX_DATAERR);
                        }
                default:
                        chars += nextchars;
        }
#ifdef DEBUG_PARSE
        std::cout << "parse: entering Ent " << name_s << std::endl;
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
                        std::cout << "        parse: Ent " << name_s << ": found field: " << field_s << " = " << value_s << std::endl;
#endif
                        fields[field_s] = value_s;
                }

                // Behavior
                else if (sscanf(s + chars, " %ms { %n", &type, &nextchars) >= 1) {
                        chars += nextchars;
                        type_s = string(type);
                        free(type);
#ifdef DEBUG_PARSE
                        std::cout << "        parse: Ent " << name_s << ": found behavior: " << type_s << "; entering" << std::endl;
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
                                        std::cout << "                parse: Ent " << name_s << ": behavior " << type_s << ": found field: " << field_s << " = " << value_s << std::endl;
#endif
                                } else {
                                        std::cerr << "parse error reading Ent " << name_s << ", behavior " << type_s << ": expected field or '}'" << std::endl;
                                        exit(EX_DATAERR);
                                }
                        }
                        chars += nextchars;
#ifdef DEBUG_PARSE
                        std::cout << "        parse: Ent " << name_s << ": leaving behavior " << type_s << std::endl;
#endif
                }

                // Error
                else {
                        std::cerr << "parse error reading Ent " << name_s << ": expected field, behavior or '}'" << std::endl;
                        exit(EX_DATAERR);
                }
        }
        chars += nextchars;
#ifdef DEBUG_PARSE
        std::cout << "parse: leaving Ent " << name_s << std::endl;
#endif

        auto it = fields.find(string("class"));
        if (it == fields.end()) {
                std::cerr << "parse error reading Ent '" << name_s << "': 'class' attribute not specified" << std::endl;
                exit(EX_DATAERR);
        } else {
                ent_class = it->second;
                if (ent_class == string("Player")) {
                        if (player != NULL) {
                                std::cerr << "parse error: player already defined" << std::endl;
                                exit(EX_DATAERR);
                        }
                        ent = player = new Player();
                }
                else if (ent_class == string("Phantom")) ent = new Phantom();
                else if (ent_class == string("RuntimePoint")) {
                        ent = new RuntimePoint(); // TODO: gráficos
                } else if (ent_class == string("RuntimeSegment")) {
                        RuntimeSegment *rs = new RuntimeSegment();

                        SET_SEGMENT_FIELD_DOUBLE_D(p1.x, -1);
                        SET_SEGMENT_FIELD_DOUBLE_D(p1.y,  0);
                        SET_SEGMENT_FIELD_DOUBLE_D(p1.z,  0);
                        SET_SEGMENT_FIELD_DOUBLE_D(p2.x,  1);
                        SET_SEGMENT_FIELD_DOUBLE_D(p2.y,  0);
                        SET_SEGMENT_FIELD_DOUBLE_D(p2.z,  0);

                        ent = rs;
                } else if (ent_class == string("RuntimeBox")) {
                        RuntimeBox *rb = new RuntimeBox();

                        SET_BOX_FIELD_DOUBLE_D(sx, 0.5);
                        SET_BOX_FIELD_DOUBLE_D(sy, 0.5);
                        SET_BOX_FIELD_DOUBLE_D(sz, 0.5);

                        ent = rb;
                } else {
                        std::cerr << "parse error reading Ent " << name_s << ": unknown class " << ent_class << std::endl;
                        exit(EX_DATAERR);
                }

                ents.push_back(ent);
        }

        ent->name = name_s;

        SET_ENT_FIELD_DOUBLE_D(pos.x, 0);
        SET_ENT_FIELD_DOUBLE_D(pos.y, 0);
        SET_ENT_FIELD_DOUBLE_D(pos.z, 0);
        SET_ENT_FIELD_DOUBLE_D(ang  , 0);
        SET_ENT_FIELD_DOUBLE_D(vel.x, 0);
        SET_ENT_FIELD_DOUBLE_D(vel.y, 0);
        SET_ENT_FIELD_DOUBLE_D(vel.z, 0);
        SET_ENT_FIELD_DOUBLE_D(vrot , 0);
        SET_ENT_FIELD_BOOL_D(collides, false);

        if (ent_class == "RuntimePoint" || ent_class == "Phantom" || ent_class == "Player") {
                DtShapeRef shape = dtNewComplexShape();
                        dtBegin(DT_SIMPLEX);
                                dtVertex(ent->pos.x, ent->pos.y, ent->pos.z);
                        dtEnd();
                dtEndComplexShape();
                dtCreateObject(static_cast<Ent *>(ent), shape);
        } else if (ent_class == "RuntimeSegment") {
                auto rs = dynamic_cast<RuntimeSegment *>(ent);
                DtShapeRef shape = dtNewComplexShape();
                        dtBegin(DT_SIMPLEX);
                                dtVertex(rs->p1.x, rs->p1.y, rs->p1.z);
                                dtVertex(rs->p2.x, rs->p2.y, rs->p2.z);
                        dtEnd();
                dtEndComplexShape();
                dtCreateObject(static_cast<Ent *>(rs), shape);
        } else if (ent_class == "RuntimeBox") {
                auto rb = dynamic_cast<RuntimeBox *>(ent);
                DtShapeRef shape = dtBox(2*(rb->sx), 2*(rb->sy), 2*(rb->sz));
                dtCreateObject(static_cast<Ent *>(rb), shape);
        }

        entses[name_s] = ent;
        behaviorses[name_s] = behaviors;

        fields.clear();

#ifdef DEBUG_PARSE
        std::cout << std::endl;
#endif

        parse_r(s, chars);
}

void parse(char *s) {
        string class_s;
        unordered_map<string, string  >::const_iterator it_fields;
        unordered_map<string, Mobile *>::const_iterator it_entses;
        Actor *p;

        parse_r(s, 0);

        for (auto it_e = behaviorses.begin(); it_e != behaviorses.end(); ++it_e) {
                for (auto it_b = it_e->second->begin(); it_b != it_e->second->end(); ++it_b) {
#ifdef DEBUG_PARSE
                        std::cout << "parse: making behavior: " << it_b->first << " for Ent " << it_e->first << std::endl;
#endif

                        it_fields = it_b->second->find(string("class"));
                        if (it_fields != it_b->second->end()) {
                                class_s = it_fields->second;
                        } else {
                                std::cerr << "parse error making Ent '" << it_e->first << "' behavior '" << it_b->first << "': required field 'class' not specified" << std::endl;
                                exit(EX_DATAERR);
                        }

                        // Align(std::string name, Mobile *character, Mobile *target, double maxAngularVelocity, double targetRadius, double slowRadius);
                        if (class_s == string("Align")) {
                                SET_BEHAVIOR_CHARACTER();
                                SET_BEHAVIOR_TARGET();
                                SET_BEHAVIOR_DOUBLE(maxAngularVelocity);
                                SET_BEHAVIOR_DOUBLE(targetRadius      );
                                SET_BEHAVIOR_DOUBLE(slowRadius        );

                                SET_P(new Align(it_e->first, character, target, maxAngularVelocity, targetRadius, slowRadius));
                                continue;
                        }

                        // Arrive(std::string name, Mobile *character, Mobile *target, double maxSpeed, double targetRadius, double slowRadius);
                        if (class_s == string("Arrive")) {
                                SET_BEHAVIOR_CHARACTER();
                                SET_BEHAVIOR_TARGET();
                                SET_BEHAVIOR_DOUBLE(maxSpeed    );
                                SET_BEHAVIOR_DOUBLE(targetRadius);
                                SET_BEHAVIOR_DOUBLE(slowRadius  );

                                SET_P(new Arrive(it_e->first, character, target, maxSpeed, targetRadius, slowRadius));
                                continue;
                        }

                        // BoundedDynamicSeparation(std::string name, Mobile *character, Mobile *target, double maxForce, double separationRadius);
                        if (class_s == string("BoundedDynamicSeparation")) {
                                SET_BEHAVIOR_CHARACTER();
                                SET_BEHAVIOR_TARGET();
                                SET_BEHAVIOR_DOUBLE(maxForce);
                                SET_BEHAVIOR_DOUBLE(separationRadius);

                                SET_P(new BoundedDynamicSeparation(it_e->first, character, target, maxForce, separationRadius));
                                continue;
                        }

                        // DynamicSeparation(std::string name, Mobile *character, Mobile *target, double minForce, double separationRadius);
                        if (class_s == string("DynamicSeparation")) {
                                SET_BEHAVIOR_CHARACTER();
                                SET_BEHAVIOR_TARGET();
                                SET_BEHAVIOR_DOUBLE(minForce);
                                SET_BEHAVIOR_DOUBLE(separationRadius);

                                SET_P(new DynamicSeparation(it_e->first, character, target, minForce, separationRadius));
                                continue;
                        }

                        // Evade(std::string name, Mobile *character, Mobile *target, double maxAcceleration);
                        if (class_s == string("Evade")) {
                                SET_BEHAVIOR_CHARACTER();
                                SET_BEHAVIOR_TARGET();
                                SET_BEHAVIOR_DOUBLE(maxSpeed);

                                SET_P(new Evade(it_e->first, character, target, maxSpeed));
                                continue;
                        }

                        // Face(std::string name, Mobile *character, Mobile *target, double maxAngularVelocity, double targetRadius, double slowRadius);
                        if (class_s == string("Face")) {
                                SET_BEHAVIOR_CHARACTER();
                                SET_BEHAVIOR_TARGET();
                                SET_BEHAVIOR_DOUBLE(maxAngularVelocity);
                                SET_BEHAVIOR_DOUBLE(targetRadius);
                                SET_BEHAVIOR_DOUBLE(slowRadius);

                                SET_P(new Face(it_e->first, character, target, maxAngularVelocity, targetRadius, slowRadius));
                                continue;
                        }

                        // Separation(std::string name, Mobile *character, Mobile *target, double maxSpeed, double separationRadius);
                        if (class_s == string("Separation")) {
                                SET_BEHAVIOR_CHARACTER();
                                SET_BEHAVIOR_TARGET();
                                SET_BEHAVIOR_DOUBLE(maxSpeed);
                                SET_BEHAVIOR_DOUBLE(separationRadius);

                                SET_P(new Separation(it_e->first, character, target, maxSpeed, separationRadius));
                                continue;
                        }

                        // KinematicArrive(std::string name, Ent *character, Ent *target, double maxSpeed, double radius);
                        if (class_s == string("KinematicArrive")) {
                                SET_BEHAVIOR_CHARACTER();
                                SET_BEHAVIOR_TARGET();
                                SET_BEHAVIOR_DOUBLE(maxSpeed);
                                SET_BEHAVIOR_DOUBLE(radius);

                                SET_P(new KinematicArrive(it_e->first, character, target, maxSpeed, radius));
                                continue;
                        }

                        // KinematicSeparation(std::string name, Ent *character, Ent *target, double maxSpeed, double separationRadius);
                        if (class_s == string("KinematicSeparation")) {
                                SET_BEHAVIOR_CHARACTER();
                                SET_BEHAVIOR_TARGET();
                                SET_BEHAVIOR_DOUBLE(maxSpeed);
                                SET_BEHAVIOR_DOUBLE(separationRadius);

                                SET_P(new KinematicSeparation(it_e->first, character, target, maxSpeed, separationRadius));
                                continue;
                        }

                        // KinematicSeek(std::string name, Ent *character, Ent *target, double maxSpeed);
                        if (class_s == string("KinematicSeek")) {
                                SET_BEHAVIOR_CHARACTER();
                                SET_BEHAVIOR_TARGET();
                                SET_BEHAVIOR_DOUBLE(maxSpeed);

                                SET_P(new KinematicSeek(it_e->first, character, target, maxSpeed));
                                continue;
                        }

                        // KinematicWander(std::string name, Ent *character, double maxSpeed, double maxRotation, double wanderTime);
                        if (class_s == string("KinematicWander")) {
                                SET_BEHAVIOR_CHARACTER();
                                SET_BEHAVIOR_DOUBLE(maxSpeed);
                                SET_BEHAVIOR_DOUBLE(maxRotation);
                                SET_BEHAVIOR_DOUBLE(wanderTime);

                                SET_P(new KinematicWander(it_e->first, character, maxSpeed, maxRotation, wanderTime));
                                continue;
                        }

                        // StaticLookWhereYoureGoing(std::string name, Mobile *character);
                        if (class_s == string("StaticLookWhereYoureGoing")) {
                                SET_BEHAVIOR_CHARACTER();

                                SET_P(new StaticLookWhereYoureGoing(it_e->first, character));
                                continue;
                        }

                        // LookWhereYoureGoing(std::string name, Mobile *character, double maxAngularVelocity, double targetRadius, double slowRadius);
                        if (class_s == string("LookWhereYoureGoing")) {
                                SET_BEHAVIOR_CHARACTER();
                                SET_BEHAVIOR_DOUBLE(maxAngularVelocity);
                                SET_BEHAVIOR_DOUBLE(targetRadius);
                                SET_BEHAVIOR_DOUBLE(slowRadius);

                                SET_P(new LookWhereYoureGoing(it_e->first, character, maxAngularVelocity, targetRadius, slowRadius));
                                continue;
                        }

                        // Pursue(std::string name, Mobile *character, Mobile *target, double maxAcceleration);
                        if (class_s == string("Pursue")) {
                                SET_BEHAVIOR_CHARACTER();
                                SET_BEHAVIOR_TARGET();
                                SET_BEHAVIOR_DOUBLE(maxSpeed);

                                SET_P(new Pursue(it_e->first, character, target, maxSpeed));
                                continue;
                        }

                        // Seek(std::string name, Mobile *character, Mobile *target, double maxAcceleration);
                        if (class_s == string("Seek")) {
                                SET_BEHAVIOR_CHARACTER();
                                SET_BEHAVIOR_TARGET();
                                SET_BEHAVIOR_DOUBLE(maxSpeed);

                                SET_P(new Seek(it_e->first, character, target, maxSpeed));
                                continue;
                        }

                        // StaticVelocityMatch(std::string name, Mobile *character, Mobile *target);
                        if (class_s == string("StaticVelocityMatch")) {
                                SET_BEHAVIOR_CHARACTER();
                                SET_BEHAVIOR_TARGET();

                                SET_P(new StaticVelocityMatch(it_e->first, character, target));
                                continue;
                        }

                        // VelocityMatch(std::string name, Mobile *character, Mobile *target, double maxAcceleration);
                        if (class_s == string("VelocityMatch")) {
                                SET_BEHAVIOR_CHARACTER();
                                SET_BEHAVIOR_TARGET();
                                SET_BEHAVIOR_DOUBLE(maxAcceleration);

                                SET_P(new VelocityMatch(it_e->first, character, target, maxAcceleration));
                                continue;
                        }

                        // Wander(std::string name, Mobile *character, Mobile *target, double maxAngularAcceleration, double maxRotation, double targetRadius, double slowRadius, double wanderOffset, double wanderRadius, double wanderRate, double wanderTime, double maxAcceleration);
                        if (class_s == string("Wander")) {
                                SET_BEHAVIOR_CHARACTER();
                                SET_BEHAVIOR_DOUBLE(maxRotation);
                                SET_BEHAVIOR_DOUBLE(targetRadius);
                                SET_BEHAVIOR_DOUBLE(slowRadius);
                                SET_BEHAVIOR_DOUBLE(wanderOffset);
                                SET_BEHAVIOR_DOUBLE(wanderRadius);
                                SET_BEHAVIOR_DOUBLE(wanderRate);
                                SET_BEHAVIOR_DOUBLE(wanderTime);
                                SET_BEHAVIOR_DOUBLE(maxAcceleration);

                                SET_P(new Wander(it_e->first, character, maxRotation, targetRadius, slowRadius, wanderOffset, wanderRadius, wanderRate, wanderTime, maxAcceleration));
                                continue;
                        }

                        // PathFollowing(std::string name, Mobile *character, Mobile *target, double maxSpeed, double targetRadius, double slowRadius);
                        if (class_s == string("PathFollowing")) {
                                SET_BEHAVIOR_CHARACTER();
                                SET_BEHAVIOR_TARGET();
                                SET_BEHAVIOR_DOUBLE(maxSpeed);
                                SET_BEHAVIOR_DOUBLE(targetRadius);
                                SET_BEHAVIOR_DOUBLE(slowRadius);

                                SET_P(new PathFollowing(it_e->first, character, target, maxSpeed, targetRadius, slowRadius));
                                continue;
                        }

                        std::cerr << "parse error making Ent '" << it_e->first << "' behavior '" << it_b->first << "': field 'class' == '" << it_fields->second << "': class not found" << std::endl;
                        exit(EX_DATAERR);
                }
        }

        if (player == NULL) {
                std::cerr << "warning: no player defined in game file; using default player." << std::endl;
                player = new Player("default player");
                ents.push_back(player);
        }

        // TODO: DELETE HEAP GARBAGE: delete behaviorses and entses.
}
