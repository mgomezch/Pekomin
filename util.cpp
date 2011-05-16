#include <sys/time.h>
#include <stdlib.h>

#include "util.hpp"

double randomBinomial() {
        struct timeval t;
        gettimeofday(&t, NULL);
        srand(t.tv_usec);

        return ((rand() % 2) - (rand() % 2));
}

double RandBin(double fMin, double fMax) {
        struct timeval t;
        gettimeofday(&t, NULL);
        srand(t.tv_usec);

        double f = (double)rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
}
