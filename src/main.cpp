/*
This is the main class driving the ray tracer.
Later this will output a gorgeous ray traced scene of various spheres
and will include some practices from my time in Operating Systems to
hopefully improve the performance of the program. :)
*/

#include "Color.h"
#include "Vec3.h"

#include <iostream>

int main(){
    //image
    int image_width = 256;
    int image_height = 256;

    //render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int h = 0; h < image_height; h++){
        for(int w = 0; w < image_width; w++){
            Color pixel_color = Color(double(w) / (image_width - 1), 
                double(h) / (image_height - 1), 0);
            write_color(std::cout, pixel_color);
        }
    }

    return 0;
}
