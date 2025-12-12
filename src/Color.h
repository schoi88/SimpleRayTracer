/**
 * This is the Color header file, it defines a utility function
 * that writes a single pixel's color to standard out stream.
*/
#ifndef COLOR_H
#define COLOR_H

#include "Vec3.h"

#include <iostream>

using Color = Vec3;

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

    //translate the component values (0-1) to an int range of (0-255)
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    //writing out the pixel color bytes
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif
