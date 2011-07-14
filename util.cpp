#include <cmath>
#include <cstdlib>

#include <sys/time.h>

#include "util.hpp"

double randomBinomial() {
        return RandBin(0, 1) - RandBin(0, 1);
}

double RandBin(double fMin, double fMax) {
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

double map_atan(double x) {
        return (2.0 * atan((M_PI * x)/2.0))/M_PI;
}
