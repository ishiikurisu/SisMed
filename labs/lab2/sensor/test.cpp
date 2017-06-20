#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NO_SAMPLES 300
using namespace std;

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
        inlet[i] = rand() % 1000 + 10;
        out_mean[i] = 0;
        out_window[i] = 0;
        out_exp[i] = 0;
    }

    // Applying filters
    // TODO Create regular mean filter
    // MEAN_FILTER mean_filter = new MEAN_FILTER();
    // TODO Create windowed mean filter
    // TODO Create exponential mean filter

    for (int i = 0; i < NO_SAMPLES; ++i)
    {
        // mean_filter.add(inlet[i]);
        // out_mean[i] = mean_filter.get();
    }

    // Writting output
    for (int i = 0; i < NO_SAMPLES; ++i)
    {
        printf("%d %.5lf %.5lf;", i*10, out_mean[i], 0);
    }
    printf("\n");

    return 0;
}
