/**
 * The Camera class contains a bulk of the functioning code for the main program.
 * This can be broken down into two main jobs including construction and dispatch
 * of rays into the world of the image and using said rays to render the image.
*/
#ifndef CAMERA_H
#define CAMERA_H

#include "Material.h"
#include "Hittable.h"
#include "Color.h"
#include "MathUtils.h"

class Camera{
    public:
        //default constructor
        Camera();

        /*
        Parameterized constructor with initializing for rendering image

        input:
            ar: the aspect ratio of image
            iw: image width
            spp: random samples taken per pixel
            md: maximum depth for ray bounces
        */
        Camera(double ar, int iw, int spp, int md);

        /*
        render the image

        input:
            world: contains the list of hittable objects that will appear in image
        */
        void render(const Hittable& world);

    private:
        double aspect_ratio;        //ratio of image width over height
        int image_width;            //rendered image width in pixel count
        int image_height;           //rendered image height in pixel count
        Point3 center;              //location of camera center
        Point3 pixel00_loc;         //location of upper left pixel in image
        Vec3 pixel_delta_u;         //offset of pixel length
        Vec3 pixel_delta_v;         //offset of pixel height
        int samples_per_pixel;      //count of random samples taken for individual pixel
        double pixel_samples_scale; //color scale factor for a sum of pixel samples
        int max_depth;              //max number of ray bounces in scene

        /*
        get a ray color for the specified Ray object you want

        input:
            r: a reference to a Ray object
            depth: recursion depth for ray bounces
            world: the 3D space the render is set in

        output:
            the ray's color
        */
        Color rayColor(const Ray& r, int depth, const Hittable& world) const;

        /*
        Construct and return a camera ray originating from camera center and
        directed at a randomly sampled point around the pixel at (x, y).

        input:
            x: x coordinate of desired pixel
            y: y coordinate of desired pixel

        output:
            the ray
        */
        Ray getRay(int x, int y) const;

        /*
        Get a vector directed to a random point in the [-0.5, -0.5] - [+0.5, +0.5]
        unit square.

        output:
            randomly directed vector
        */
        Vec3 sampleSquare() const;
};

#endif
