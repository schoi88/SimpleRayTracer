/**
 * Vec3 is a class for vectors to be used for various objects for the program.
 * These uses can include color, location, direction, and offsets. 
*/
#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class Vec3{
    public:
        //the array of vector values
        double e[3];

        //constructors
        Vec3() : e{0, 0, 0} {}
        Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        //return x value
        double x() const{
            return e[0];
        }

        //return y value
        double y() const{
            return e[1];
        }

        //return z value
        double z() const{
            return e[2];
        }

        //return the vector with negative values
        Vec3 operator-() const{
            return Vec3(-e[0], -e[1], -e[2]);
        }

        //return value at index i 
        double operator[](int i) const{
            return e[i];
        }

        //return a reference to value at index i
        double& operator[](int i){
            return e[i];
        }

        /*
        vector addition

        input:
            v: the vector whose values are being added

        output:
            The reference of the vector after adding values from v.
        */
        Vec3& operator+=(const Vec3& v){
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        /*
        vector scalar multiplication

        input:
            t: the scalar
        
        output:
            The reference of the product of the multiplication.
        */
        Vec3& operator*=(double t){
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        /*
        vector division by scalar

        input:
            t: the scalar
        
        output:
            The reference of the vector after magnitude is reduced by scalar.
        */
        Vec3& operator/=(double t){
            return *this *= (1 / t);
        }

        //return the sum of vector's values
        double length() const{
            return std::sqrt(lengthSquared());
        }        

        //return the sum of vector's values squared
        double lengthSquared() const{
            return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; 
        }
};

//a Vec3 alias
using Point3 = Vec3;

//utility functions

/*
write out this vector to standard output stream

input:
    out: the output stream
    v: the vector

output:
    An output stream with values from v.
*/
inline std::ostream& operator<<(std::ostream& out, const Vec3& v){
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

/*
vector addition

input:
    u: a vector
    v: another vector

output:
    A new vector that is the sum of u and v.
*/
inline Vec3 operator+(const Vec3& u, const Vec3& v){
    return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

/*
vector subtraction

input:
    u: the vector whose values are being subtracted by v
    v: the vector containing the values being subtracted

output:
    A new vector that is the difference of u by v.
*/
inline Vec3 operator-(const Vec3& u, const Vec3& v){
    return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

/*
dot product

input:
    u: a vector
    v: another vector

output:
    A new vector whose values are the product of u and v.
*/
inline Vec3 operator*(const Vec3& u, const Vec3& v){
    return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

/*
scalar multiplication

input:
    t: the scalar
    v: the vector

output:
    A new vector whose values are v multiplied by t.
*/
inline Vec3 operator*(double t, const Vec3& v){
    return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

//more scalar multiplication
inline Vec3 operator*(const Vec3& v, double t){
    return t * v;
}

/*
vector division by scalar

input:
    v: the vector
    t: the scalar

output:
    The vector v scaled down by t.
*/
inline Vec3 operator/(const Vec3& v, double t){
    return (1 / t) * v;
}

/*
dot product

input:
    u: the vector being dotted
    v: the vector u is dotted by

output:
    The vector u dotted by v.
*/
inline double dot(const Vec3& u, const Vec3& v){
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

/*
cross product

input:
    u: a vector
    v: another vector

output:
    A new vector that is perpendicular to u and v.
*/
inline Vec3 cross(const Vec3& u, const Vec3& v){
    return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

//return the unit vector of v
inline Vec3 unitVector(const Vec3& v){
    return v / v.length();
}

#endif
