#ifndef FILTERS_H
#define FILTERS_H

class MEAN_FILTER
{
    double current_mean;
    int number_values;
public:
    MEAN_FILTER();
    void add(double);
    double get();
};

class WINDOW_FILTER
{
    int window_size;
    double* values;
public:
    WINDOW_FILTER(int);
    void add(double);
    double get();
};

#endif
