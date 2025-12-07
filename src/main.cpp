/**
 * This is the main class driving the ray tracer.
 * Later this will output a gorgeous ray traced scene of various spheres
 * and will include some practices from my time in Operating Systems to
 * hopefully improve the performance of the program. :)
*/

#include "Color.h"
#include "Ray.h"
#include "Vec3.h"

#include <iostream>

/*
determine if ray "r" is located within a sphere's area in scene and output the
result of the calculation.

input:
    center: a point object which is the location of the center of a sphere
    radius: the distance of the sphere's radius from center
    r: the ray of light from camera location

output:
    the resulting value if r is intersecting or is tangent to the area of the 
    sphere determined using quadratic formula. When discriminant is greater than
    1 there is an intersection with the sphere object, 0 for when there is a 
    point of tangency, or negative signifying no intersection.
*/
double hit_sphere(const Point3& center, double radius, const Ray& r){
    Vec3 oc = center - r.origin();
    double a = r.direction().length_squared();
    double b = dot(r.direction(), oc);
    double c = oc.length_squared() - radius * radius;
    double discriminant = b * b - a * c;

    if(discriminant < 0){
        return -1.0;
    }else{
        return (b - std::sqrt(discriminant)) / a;
    }
}

/*
get a ray color for the specified Ray object you want

input:
    r: a reference to a Ray object

output:
    the ray's color
*/
Color ray_color(const Ray& r){
    double t = hit_sphere(Point3(0, 0, -1), 0.5, r);

    if(t > 0.0){
        Vec3 N = unit_vector(r.at(t) - Vec3(0, 0, -1));
        return 0.5 * Color(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    Vec3 unit_direction = unit_vector(r.direction());
    double a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

int main(){
    //image
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    //calculate image height depending on desired aspect ratio
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height; 

    //camera
    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * 
        (double(image_width) / image_height);
    Point3 camera_center = Point3(0, 0, 0);

    //vectors accross horizontal and vertical viewport edges
    Vec3 viewport_u = Vec3(viewport_width, 0, 0);
    Vec3 viewport_v = Vec3(0, -viewport_height, 0);

    //delta values for change in vector from pixel to pixel
    Vec3 pixel_delta_u = viewport_u / image_width;
    Vec3 pixel_delta_v = viewport_v / image_height;

    //find location of top left pixel (the start of the viewport)
    Vec3 viewport_upper_left = camera_center - Vec3(0, 0, focal_length) - 
        (viewport_u / 2) - (viewport_v / 2);
    Vec3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + 
        pixel_delta_v);

    //rendering
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int h = 0; h < image_height; h++){
        for(int w = 0; w < image_width; w++){
            Vec3 pixel_center = pixel00_loc + (w * pixel_delta_u) + (h * 
                pixel_delta_v);
            Vec3 ray_direction = pixel_center - camera_center;
            Ray r = Ray(camera_center, ray_direction);
            Color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    return 0;
}
