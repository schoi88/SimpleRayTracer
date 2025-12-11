/**
 * This is the main class driving the ray tracer.
 * Later this will output a gorgeous ray traced scene of various spheres
 * and will include some practices from my time in Operating Systems to
 * hopefully improve the performance of the program. :)
*/

#include "Rtcommon.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"

/*
get a ray color for the specified Ray object you want

input:
    r: a reference to a Ray object
    world: the 3D space the render is set in

output:
    the ray's color
*/
Color rayColor(const Ray& r, const Hittable& world){
    HitRecord rec;
    if(world.hit(r, 0, INF, rec)){
        return 0.5 * (rec.normal + Color(1, 1, 1));
    }

    Vec3 unit_direction = unitVector(r.direction());
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

    //world
    HittableList world;
    world.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

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
            Color pixel_color = rayColor(r, world);
            writeColor(std::cout, pixel_color);
        }
    }

    return 0;
}
