#include <sys/time.h>
#include <stdlib.h>
#include <math.h>

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

double mapToRange(double value) {
        while (value < -M_PI || M_PI < value) {
                if (value > M_PI) {
                        value -= 2 * M_PI;
                } else if(value < -M_PI) {
                        value += 2 * M_PI;
                }
        }
        return value;
}

