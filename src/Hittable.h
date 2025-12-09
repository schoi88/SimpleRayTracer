/**
 * Hittable is an abstraction meant to assist its inheritors (other objects used 
 * in ray tracer like a sphere) for when a ray "hits" them.
*/
#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"

//record object to hold hit data for a ray
class HitRecord{
    public:
        //the point on ray where hit is detected
        Point3 p;
        //the surface of object where hit is detected
        Vec3 normal;
        //the root value of hit (result of quadratic formula)
        double t;
};

class Hittable{
    public:
        //destructor for Hittable objects
        virtual ~Hittable() = default;

        /*
        hit abstraction for Hittable objects

        input:
            r: the ray that may be hitting object
            ray_tmin: the lower bound of the viable hit interval
            ray_tmax: the upper bound of the viable hit interval
            rec: the HitRecord of whose values are set to the data calculated
                if hit is found.

        output:
            True if intersection or graze is found (discriminant != 0 and root is
            within acceptable interval) or false if no hit is detected 
            (discriminant < 0).
        */
        virtual bool hit(const Ray& r, double ray_tmin, double ray_tmax, 
                         HitRecord& rec) const = 0;    
};

#endif