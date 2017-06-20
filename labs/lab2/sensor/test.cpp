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
        printf("%d %.5lf %.5lf;", i*10, proc[i], ref[i]);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    // Setup of test environment
    double* inlet = (double*) malloc(sizeof(double) * NO_SAMPLES);
    double* out_mean = (double*) malloc(sizeof(double) * NO_SAMPLES);
    double* out_window = (double*) malloc(sizeof(double) * NO_SAMPLES);
    double* out_exp = (double*) malloc(sizeof(double) * NO_SAMPLES);

    srand(time(NULL));
    for (int i = 0; i < NO_SAMPLES; ++i)
    {
        inlet[i] = 420 + (rand() % 20 - 40);
        out_mean[i] = 0;
        out_window[i] = 0;
        out_exp[i] = 0;
    }

    // Applying filters
    MEAN_FILTER mean_filter;
    // TODO Create windowed mean filter
    WINDOW_FILTER window_filter(10);
    // TODO Create exponential mean filter

    for (int i = 0; i < NO_SAMPLES; ++i)
    {
        mean_filter.add(inlet[i]);
        window_filter.add(inlet[i]);
        out_mean[i] = mean_filter.get();
        out_window[i] = window_filter.get();
    }

    // Writting output
    write(inlet, out_mean);
    write(inlet, out_window);

    return 0;
}
