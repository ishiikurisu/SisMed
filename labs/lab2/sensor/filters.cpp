#include "stdlib.h"
#include "./filters.h"
#define MEAN_FILTER_KIND 8
#define WINDOW_FILTER_KIND 9
#define EXP_FILTER_KIND 10
#define KALMAN_FILTER_KIND 11

/* #########
   # TOOLS #
   ######### */

double FILTERS_MEAN(int how_many, double* what)
{
    double mean = 0;

    for (int i = 0; i < how_many; i++)
    {
        mean += what[i];
    }

    return mean/how_many;
}

/* ##########################
   # MEAN FILTER DEFINITION #
   ########################## */

MEAN_FILTER::MEAN_FILTER()
{
    this->current_mean = 0;
    this->number_values = 0;
}

void MEAN_FILTER::add(double inlet)
{
    number_values++;
    current_mean = (number_values-1)*current_mean/number_values + inlet/number_values;
}

double MEAN_FILTER::get()
{
    return this->current_mean;
}

/* ############################
   # WINDOW FILTER DEFINITION #
   ############################ */

WINDOW_FILTER::WINDOW_FILTER(int window_size)
{
    this->window_size = window_size;
    this->values = (double*) malloc(sizeof(double) * this->window_size);

    for (int i = 0; i < this->window_size; ++i)
    {
        this->values[i] = 0;
    }
}

WINDOW_FILTER::~WINDOW_FILTER()
{
    free(this->values);
}

void WINDOW_FILTER::add(double inlet)
{
    for (int i = 1; i < this->window_size; ++i)
    {
        this->values[i] = this->values[i-1];
    }
    this->values[0] = inlet;
}

double WINDOW_FILTER::get()
{
    return FILTERS_MEAN(this->window_size, this->values);
}

/* #####################################
   # EXPONENTIAL FILTER IMPLEMENTATION #
   ##################################### */

EXP_FILTER::EXP_FILTER(double alpha)
{
    this->alpha = alpha;
    this->current_mean = 0;
}

void EXP_FILTER::add(double inlet)
{
    current_mean = alpha*current_mean + (1-alpha)*inlet;
}

double EXP_FILTER::get()
{
    return this->current_mean;
}

/* ################################
   # KALMAN FILTER IMPLEMENTATION #
   ################################ */

KALMAN_FILTER::KALMAN_FILTER()
{
    xp = 0;
    Pp = 0;
    P = 1;
    K = 0;
    A = 1;
    Q = 1;
    R = 1;
    H = 1;
    x = 0;
}

void KALMAN_FILTER::add(double z)
{
    xp = A*x;
    Pp = A*P*A +Q;
    K = Pp*H*1/(H*Pp*H + R);
    x = xp + K*(z-H*xp);
    P = Pp - K*H*Pp;
}

double KALMAN_FILTER::get()
{
    return x;
}
