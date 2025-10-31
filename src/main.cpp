/*
This is the main class driving the ray tracer.
Later this will output a gorgeous ray traced scene of various spheres
and will include some practices from my time in Operating Systems to
hopefully improve the performance of the program. :)
*/

#include <iostream>

int main(){
    //image
    int image_width = 256;
    int image_height = 256;

    //render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int h = 0; h < image_height; h++){
        for(int w = 0; w < image_width; w++){
            double r = double(w) / (image_width - 1);
            double g = double(h) / (image_height - 1);
            double b = 0.0;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    return 0;
}
