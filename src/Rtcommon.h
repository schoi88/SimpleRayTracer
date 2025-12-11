/**
 * Rtcommon is the common header file which contains commonly used utility and 
 * constants to be used by the renderer.
*/
#ifndef RTCOMMON_H
#define RTCOMMON_H

//common headers
#include "Color.h"
#include "Ray.h"
#include "Vec3.h"

//includes for common headers
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

//useful constants
const double INF = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

/*
get radian value from given degrees.

input:
    degrees: degrees to turn to radians
*/
inline double degreesToRadians(double degrees){
    return degrees * PI / 180.0;
}

#endif