/**
 * Math Utilities
*/
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include "Constants.h"

//get radian value from given degrees
inline double degreesToRadians(double degrees){
    return degrees * PI / 180.0;
}

#endif