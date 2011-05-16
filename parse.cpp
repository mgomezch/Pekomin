#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

#include <vector>

#include "game.hpp"
#include "parse.hpp"

#define DEBUG_PARSE

using namespace std;

void parse(char *s, int chars) {
        char *name, *type, *field, *value;
        vector< pair< char *, char * > > fields;
        vector< pair< char *, vector< pair< char *, char * > > > > behaviors;
        int nextchars;

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
        // TODO: for each behavior: parse fields, instantiate behavior, set fields, add to ent
        // TODO: add new ent to ents
        // TODO: DELETE HEAP GARBAGE: free() ALL strings made by ssprintf("%m[]")

        parse(s, chars);
}
