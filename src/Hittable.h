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
        /*
        front_face will determine which side (inside or outside) of the surface
        of an object the ray is originating from, which can be important for how
        light will affect objects with different materials like metal or glass.
        */
        bool front_face;

        /*
        This function will set the side of the surface a ray is coming from.
        It can be determined by using a dot product of the ray's direction and
        the outward_normal of the object.

        ***outward_normal will need to be of unit length, this is to be done in
           object classes as it will be dependent on the object's geometric shape.

        input:
            r: the ray
            outward_normal: the outside surface of the object

        output:
            True if ray is outside the object (dot product is < 0) or false if
            ray is within the surface of object (dot product is > 0).
        */
        void set_face_normal(const Ray& r, const Vec3& outward_normal){
            front_face = dot(r.direction(), outward_normal) < 0;
            normal = front_face ? outward_normal : -outward_normal;
        }
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