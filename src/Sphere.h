/**
 * The Sphere class houses the code for Sphere objects and their ray hit 
 * computation.
*/

#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"
#include "Vec3.h"
#include "Material.h"

#include <memory>

class Sphere : public Hittable{
    public:
        /*
        Sphere constructor

        input:
            center: a Point3 object that is the origin of the sphere
            radius: sphere's radius as a double
        */
        Sphere(const Point3& center, double radius, std::shared_ptr<Material> mat);
        
        /*
        Used to calculate if a ray makes contact with a Sphere object.

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
        bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override;

    private:
        Point3 center;
        double radius;
        std::shared_ptr<Material> mat;
};

#endif