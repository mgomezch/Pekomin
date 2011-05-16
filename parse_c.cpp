#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#include <vector>

#include "game.hpp"
#include "Mobile.hpp"
#include "parse.hpp"
#include "Player.hpp"
#include "RuntimePekomin.hpp"

#define DEBUG_PARSE

using namespace std;

vector< pair< pair<char *, Ent *>, vector< pair< char *, vector< pair< char *, char * > > > > > > descriptors;

vector<string *>  strings;

void parse_r(char *s, int chars) {
        bool p;
        unsigned int i, n;
        char   *name  , *type  , *field  , *value  ;
        string  name_s,  type_s,  field_s,  value_s;
        pair<string, string> kv;
        vector< pair< string *, string * > > fields;
        vector< pair< string *, vector< pair< char *, char * > > > > behaviors;
        int nextchars;
        Mobile *ent;

#ifdef DEBUG_PARSE
        printf("parse: starting at %p + %d\n", s, chars); // DEBUG
#endif

        switch (sscanf(s + chars, " %ms %n", &name, &nextchars)) {
                case 0:
                        fprintf(stderr, "parse error reading name\n");
                        exit(EX_DATAERR);
                case EOF:
                        return;
                default:
                        chars += nextchars;
        }
#ifdef DEBUG_PARSE
        printf("parse: read ent name %s\n", name); // DEBUG
#endif

        nextchars = -1;
        switch(sscanf(s + chars, " { %n", &nextchars)) {
                case 0:
                case EOF:
                        if (nextchars == -1) {
                                fprintf(stderr, "parse error reading ent %s: expected '{'\n", name);
                                exit(EX_DATAERR);
                        }
                default:
                        chars += nextchars;
        }
#ifdef DEBUG_PARSE
        printf("parse: entering ent %s\n", name); // DEBUG
#endif

        while (nextchars = -1, sscanf(s + chars, " } %n", &nextchars), nextchars == -1) {
#ifdef DEBUG_PARSE
//              printf("parse: ent %s: found something that isn't '}'\n", name); // DEBUG
#endif
                // Field
                field = value = NULL;
                if (sscanf(s + chars, " %m[a-zA-Z_0-9.] = %m[a-zA-Z_0-9.] ;%n", &field, &value, &nextchars) >= 2) {
                        chars += nextchars;
                        fields.push_back(pair<char *, char *>(field, value));
#ifdef DEBUG_PARSE
                        printf("        parse: ent %s: found field: %s = %s\n", name, field, value); // DEBUG
#endif
                }

                // Behavior
                else if (sscanf(s + chars, " %ms { %n", &type, &nextchars) >= 1) {
                        chars += nextchars;
#ifdef DEBUG_PARSE
                        printf("        parse: ent %s: found behavior: %s; entering\n", name, type); // DEBUG
#endif

                        behaviors.push_back(pair<char *, vector< pair< char *, char * > > >(type, vector< pair< char *, char * > >()));
                        while (nextchars = -1, sscanf(s + chars, " } %n", &nextchars), nextchars == -1) {
#ifdef DEBUG_PARSE
//                              printf("parse: ent %s: behavior %s: found something that isn't '}'\n", name, type); // DEBUG
#endif

                                field = value = NULL;
                                if (sscanf(s + chars, " %m[a-zA-Z_0-9.] = %m[a-zA-Z_0-9.] ; %n", &field, &value, &nextchars) >= 2) {
                                        chars += nextchars;
                                        behaviors.back().second.push_back(pair<char *, char *>(field, value));
#ifdef DEBUG_PARSE
                                        printf("                parse: ent %s: behavior %s: found field: %s = %s\n", name, type, field, value); // DEBUG
#endif
                                } else {
                                        fprintf(stderr, "parse error reading ent %s, behavior %s: expected field or '}'\n", name, type);
                                        exit(EX_DATAERR);
                                }
                        }
                        chars += nextchars;
#ifdef DEBUG_PARSE
                        printf("        parse: ent %s: leaving behavior %s\n", name, type); // DEBUG
#endif
                }

                // Error
                else {
                        fprintf(stderr, "parse error reading ent %s: expected field, behavior or '}'\n", name);
                        exit(EX_DATAERR);
                }
        }
        chars += nextchars;
#ifdef DEBUG_PARSE
                        printf("parse: leaving ent %s\n", name); // DEBUG
#endif

        // TODO: parse fields, instantiate ent, set fields
        p = (strcmp(name, "player") == 0);
        
        if (p) {
                if (player != NULL) {
                        fprintf(stderr, "parse error: player already defined\n");
                        exit(EX_DATAERR);
                }
                ent = player = new Player();
        } else {
                ent = new RuntimePekomin();
                ents.push_back(ent);
        }

        for (i = 0; i < fields.size(); i++) {
                field = fields[i].first;
                value = fields[i].second;
                if (strcmp(field, "pos.x") == 0) {
                        if (sscanf(value, "%i", &n) != 1) {
                                fprintf(stderr, "parse error reading ent field %s = %s\n", field, value);
                                exit(EX_DATAERR);
                        }
                        ent->pos.x = n;
                } else if (strcmp(field, "pos.y") == 0) {
                        if (sscanf(value, "%i", &n) != 1) {
                                fprintf(stderr, "parse error reading ent field %s = %s\n", field, value);
                                exit(EX_DATAERR);
                        }
                        ent->pos.y = n;
                } else if (strcmp(field, "pos.z") == 0) {
                        if (sscanf(value, "%i", &n) != 1) {
                                fprintf(stderr, "parse error reading ent field %s = %s\n", field, value);
                                exit(EX_DATAERR);
                        }
                        ent->pos.z = n;
                } else if (strcmp(field, "vel.x") == 0) {
                        if (sscanf(value, "%i", &n) != 1) {
                                fprintf(stderr, "parse error reading ent field %s = %s\n", field, value);
                                exit(EX_DATAERR);
                        }
                        ent->vel.x = n;
                } else if (strcmp(field, "vel.y") == 0) {
                        if (sscanf(value, "%i", &n) != 1) {
                                fprintf(stderr, "parse error reading ent field %s = %s\n", field, value);
                                exit(EX_DATAERR);
                        }
                        ent->vel.y = n;
                } else if (strcmp(field, "vel.z") == 0) {
                        if (sscanf(value, "%i", &n) != 1) {
                                fprintf(stderr, "parse error reading ent field %s = %s\n", field, value);
                                exit(EX_DATAERR);
                        }
                        ent->vel.z = n;
                }
        }

        while (!fields.empty()) {
                kv = fields.back();
                fields.pop_back();
                free(kv.first);
                free(kv.second);
        }
        
        descriptors.push_back(pair< pair<char *, Ent *>, vector< pair< char *, vector< pair< char *, char * > > > > >(pair<char *, Ent *>(name, ent), behaviors));

        parse_r(s, chars);
}

void parse(char *s) {
        unsigned int i, j;
        pair< pair<char *, Ent *>, vector< pair< char *, vector< pair< char *, char * > > > > > descriptor;

        parse_r(s, 0);

        for (i = 0; i < descriptors.size(); i++) {
                for (j = 0; j < descriptors[i].second.size(); j++) {
                        if (1) descriptors[i].second[j].first;
                }
        }
        // TODO: for each behavior: parse fields, instantiate behavior, set fields, add to ent
        // TODO: DELETE HEAP GARBAGE: free() ALL strings made by ssprintf("%m[]")
}

