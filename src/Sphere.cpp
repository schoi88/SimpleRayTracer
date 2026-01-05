#include "Sphere.h"

Sphere::Sphere(const Point3& center, double radius, 
               std::shared_ptr<Material> mat) : center(center), 
               radius(std::fmax(0, radius)), mat(mat){}

bool Sphere::hit(const Ray& r, Interval ray_t, HitRecord& rec) const{
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
    if(!ray_t.surrounds(root)){
        root = (h + sqrt_discriminant) / a;
        if(!ray_t.surrounds(root)){
            return false;
        }
    }

    //set hit record data
    rec.t = root;
    rec.p = r.at(rec.t);
    rec.normal = (rec.p - center) / radius;
    rec.mat = mat;

    return true;
}
