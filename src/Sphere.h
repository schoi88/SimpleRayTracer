/**
 * The Sphere class houses the code for Sphere objects and their ray hit 
 * computation.
*/

#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"
#include "Vec3.h"

class Sphere : public Hittable{
    private:
        Point3 center;
        double radius;
    
    public:
        /*
        Sphere constructor

        input:
            center: a Point3 object that is the origin of the sphere
            radius: sphere's radius as a double
        */
        Sphere(const Point3& center, double radius) : center(center), 
               radius(std::fmax(0, radius)){}
        
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
        bool hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) 
                 const override{
            //values for quadratic formula to find ray intersections
            Vec3 oc = center - r.origin();
            double a = r.direction().lengthSquared();
            double h = dot(r.direction(), oc);
            double c = oc.lengthSquared() - radius * radius;
            /*
            if discriminant < 0 no hit detected
            if discriminant = 0 hit is a surface graze (1 point of intersection)
            if discriminant > 0 hit has 2 intersections on object
            */
            double discriminant = h * h - a * c;
            
            //no hit detected
            if(discriminant < 0){
                return false;
            }

            double sqrt_discriminant = std::sqrt(discriminant);

            //find nearest root (t) that is within the acceptable range
            double root = (h - sqrt_discriminant) / a;
            if(root <= ray_tmin || root >= ray_tmax){
                root = (h + sqrt_discriminant) / a;
                if(root <= ray_tmin || root >= ray_tmax){
                    return false;
                }
            }

            //set hit record data
            rec.t = root;
            rec.p = r.at(rec.t);
            rec.normal = (rec.p - center) / radius;

            return true;
        }
};

#endif