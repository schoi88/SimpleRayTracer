/**
 * This is a header containing the Ray class. A ray can be thought of as a 
 * half-line in 3D space and will have a calculation for what color can be seen 
 * on the ray. A ray also consists of two components which include an origin 
 * point and a direction. 
*/

#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class Ray{
    private:
        //the origin of the ray
        Point3 orig;
        //direction where ray is pointing to
        Vec3 dir;

    public:
        //default constructor
        Ray(){}

        /*
        constructor

        input:
            origin: a Point3 object which is the original location of the ray
            direction: the direction of the ray as a Vec3 object
        */
        Ray(const Point3& origin, const Vec3& direction){
            orig = origin;
            dir = direction;
        }

        //return origin
        const Point3& origin() const{
            return orig;
        }

        //return direction
        const Vec3& direction() const{
            return dir;
        }

        /*
        Represent a point on the ray's 3D position as a function

        input:
            t: a number used to move to a point on the ray in 3D space. When t
                is poisitive you are given the ray's space from t and past the 
                origin onward to the end of the ray while negative t values can 
                be used to go to any location along the ray.

        output:
            A subsection or entirety of the ray.  
        */
        Point3 at(double t) const {
            return orig + t * dir;
        }
};

#endif
