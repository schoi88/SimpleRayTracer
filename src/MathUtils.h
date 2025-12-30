/**
 * Math Utilities
*/
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include "Constants.h"

#include <random>

//get radian value from given degrees
inline double degreesToRadians(double degrees){
    return degrees * PI / 180.0;
}

//get a random real number within range [0, 1)
inline double randomDouble(){
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

//get a random real number within range [min , max)
inline double randomDouble(double min, double max){
    return min + (max - min) * randomDouble();
}

#endif