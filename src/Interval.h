/**
 * Interval class is to add more simplicity by seperating commonly used code from
 * other classes into its own object. 
*/
#ifndef INTERVAL_H
#define INTERVAL_H

#include "Constants.h"

class Interval{
    public:
        double min;
        double max;

        //default constructor
        Interval() : min(+INF), max(-INF) {}

        /*
        constructor

        input:
            min: lower bound of interval
            max: upper bound of interval
        */
        Interval(double min, double max) : min(min), max(max) {}

        
        //return the size of this interval
        double size() const{
            return max - min;
        }

        //does this interval contain x inclusively
        bool contains(double x) const{
            return min <= x && max >= x;
        }

        //are interval bounds outside of x
        bool surrounds(double x) const{
            return min < x && max > x;
        }

        static const Interval empty;
        static const Interval universe;
};

const Interval Interval::empty = Interval(+INF, -INF);
const Interval Interval::universe = Interval(-INF, +INF);

#endif