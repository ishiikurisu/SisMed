#include "./filters.h"

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
