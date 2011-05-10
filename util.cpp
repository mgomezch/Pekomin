#include <sys/time.h>
#include <stdlib.h>

#include "util.hpp"

int randomBinomial() {
        struct timeval t;
        gettimeofday(&t, NULL);
        srand(t.tv_usec);

        return ((rand() % 2) - (rand() % 2));
}
