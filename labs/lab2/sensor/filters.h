#ifndef MEAN_FILTER_H
#define MEAN_FILTER_H

class MEAN_FILTER
{
    double current_mean;
    int number_values;
public:
    MEAN_FILTER();
    void add(double);
    double get();
};

#endif
