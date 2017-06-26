#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./filters.h"
#define NO_SAMPLES 300
using namespace std;

void write(double* ref, double* proc)
{
    for (int i = 0; i < NO_SAMPLES; ++i)
    {
        printf("%d;%.5lf;%.5lf\n", i*10, proc[i], ref[i]);
    }
}

int main(int argc, char const *argv[])
{
    KALMAN_FILTER filter;
    double* inlet = (double*) malloc(sizeof(double) * NO_SAMPLES);
    double* outlet = (double*) malloc(sizeof(double) * NO_SAMPLES);
    srand(time(NULL));
    for (int i = 0; i < NO_SAMPLES; ++i)
    {
        inlet[i] = 420 + (rand() % 20 - 40);
        outlet[i] = 0;
    }

    for (int i = 0; i < NO_SAMPLES; ++i)
    {
        filter.add(inlet[i]);
        outlet[i] = filter.get();
    }

    write(inlet, outlet);
    return 0;
}
