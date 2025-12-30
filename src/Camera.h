/**
 * The Camera class contains a bulk of the functioning code for the main program.
 * This can be broken down into two main jobs including construction and dispatch
 * of rays into the world of the image and using said rays to render the image.
*/
#ifndef CAMERA_H
#define CAMERA_H

#include "Hittable.h"
#include "Color.h"
#include "MathUtils.h"

const int samples_per_pixel = 100;
const double pixel_samples_scale = 1.0 / samples_per_pixel;

class Camera{
    private:
        double aspect_ratio;
        int image_width;
        int image_height;
        Point3 center;
        Point3 pixel00_loc;
        Vec3 pixel_delta_u;
        Vec3 pixel_delta_v;

        /*
        get a ray color for the specified Ray object you want

        input:
            r: a reference to a Ray object
            world: the 3D space the render is set in

        output:
            the ray's color
        */
        Color rayColor(const Ray& r, const Hittable& world) const{
            HitRecord rec;
            if(world.hit(r, Interval(0, INF), rec)){
                return 0.5 * (rec.normal + Color(1, 1, 1));
            }

            Vec3 unit_direction = unitVector(r.direction());
            double a = 0.5 * (unit_direction.y() + 1.0);
            return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
        }

        /*
        Construct and return a camera ray originating from camera center and
        directed at a randomly sampled point around the pixel at (x, y).

        input:
            x: x coordinate of desired pixel
            y: y coordinate of desired pixel

        output:
            the ray
        */
        Ray getRay(int x, int y) const{
            Vec3 offset = sampleSquare();
            Vec3 pixel_sample = pixel00_loc + ((x + offset.x()) * pixel_delta_u) +
                ((y + offset.y()) * pixel_delta_v);
            
            Point3 ray_origin = center;
            Vec3 ray_direction = pixel_sample - ray_origin;

            return Ray(ray_origin, ray_direction);
        }

        /*
        Get a vector directed to a random point in the [-0.5, -0.5] - [+0.5, +0.5]
        unit square.

        output:
            randomly directed vector
        */
        Vec3 sampleSquare() const{
            return Vec3(randomDouble() - 0.5, randomDouble() - 0.5, 0);
        }

    public:
        //default constructor
        Camera(){}

        /*
        Parameterized constructor with initializing for rendering image

        input:
            ar: the aspect ratio of image
            iw: image width
        */
        Camera(double ar, int iw){
            aspect_ratio = ar;
            image_width = iw;

            image_height = static_cast<int>(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            center = Point3(0, 0, 0);

            //viewport dimensions
            double focal_length = 1.0;
            double viewport_height = 2.0;
            double viewport_width = viewport_height * 
                (static_cast<double>(image_width) / image_height);

            //Calculate vectors along horizontal and vertical viewport edges
            Vec3 viewport_u = Vec3(viewport_width, 0, 0);
            Vec3 viewport_v = Vec3(0, -viewport_height, 0);

            //Calculate horizontal and vertical delta vectors between pixels
            pixel_delta_u = viewport_u / image_width;
            pixel_delta_v = viewport_v / image_height;

            //Calculate location of upper left pixel
            Vec3 viewport_upper_left = center - Vec3(0, 0, focal_length) - 
                viewport_u / 2 - viewport_v / 2;
            pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
        }

        /*
        render the image

        input:
            world: contains the list of hittable objects that will appear in image
        */
        void render(const Hittable& world){
            std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

            for(int h = 0; h < image_height; h++){
                for(int w = 0; w < image_width; w++){
                    /*
                    Point3 pixel_center = pixel00_loc + (w * pixel_delta_u) + 
                        (h * pixel_delta_v);
                    Vec3 ray_direction = pixel_center - center;
                    Ray r = Ray(center, ray_direction);

                    Color pixel_color = rayColor(r, world);
                    writeColor(std::cout, pixel_color);
                    */
                    Color pixelColor = Color(0, 0, 0);
                    for(int sample = 0; sample < samples_per_pixel; sample++){
                        Ray r = getRay(w, h);
                        pixelColor += rayColor(r, world);
                    }
                    writeColor(std::cout, pixel_samples_scale * pixelColor);
                }
            }
        }
};

#endif
