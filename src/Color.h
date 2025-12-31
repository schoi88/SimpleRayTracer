/**
 * This is the Color header file, it defines a utility function
 * that writes a single pixel's color to standard out stream.
*/
#ifndef COLOR_H
#define COLOR_H

#include "Vec3.h"
#include "Interval.h"

#include <iostream>

using Color = Vec3;

/*
transform a color component from linear to gamma color space

input:
    linear_component: the color component in linear color space

output:
    the gamma corrected color component
*/
inline double linearToGamma(double linear_component){
    if(linear_component > 0){
        return std::sqrt(linear_component);
    }

    return 0;
}

/*
write out a single pixel's color using the three values of its vector
to translate its rgb values.

input:
    out: standard out stream being used
    pixel_color: a Vec3 object containing the rgb values
*/
void writeColor(std::ostream& out, const Color& pixel_color){
    double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();

    //apply gamma correction
    r = linearToGamma(r);
    g = linearToGamma(g);
    b = linearToGamma(b);

    //translate the component values (0-1) to an int range of (0-255)
    static const Interval intensity = Interval(0.000, 0.999);
    int rbyte = static_cast<int>(255.999 * intensity.clamp(r));
    int gbyte = static_cast<int>(255.999 * intensity.clamp(g));
    int bbyte = static_cast<int>(255.999 * intensity.clamp(b));

    //writing out the pixel color bytes
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif
