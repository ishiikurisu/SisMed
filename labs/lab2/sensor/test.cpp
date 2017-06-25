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
    double* inlet = (double*) malloc(sizeof(double) * NO_SAMPLES);
    double* out_kalman = (double*) malloc(sizeof(double) * NO_SAMPLES);
    srand(time(NULL));
    for (int i = 0; i < NO_SAMPLES; ++i)
    {
        inlet[i] = 420 + (rand() % 20 - 40);
        out_kalman[i] = 0;
    }

    KALMAN_FILTER kalman_filter;
    for (int i = 0; i < NO_SAMPLES; ++i)
    {
        kalman_filter.add(inlet[i]);
        out_kalman[i] = kalman_filter.get();
    }

    write(inlet, out_kalman);
    return 0;
}
