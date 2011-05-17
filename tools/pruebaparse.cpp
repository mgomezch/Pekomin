#include "../parse.cpp"
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 65536

int main(int argc, char **argv) {
        char buf[BUFSIZE];
        int pos = 0;

        while (!feof(stdin)) pos += fread(&buf + pos, sizeof(char), BUFSIZE, stdin);
        buf[pos] = '\0';
        parse(buf);
}
