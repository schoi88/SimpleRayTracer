/**
 * The HittableList class is used to store world objects through the use of
 * shared pointers which also is capable of managing the memory this class will
 * be using. 
*/
#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "Hittable.h"

#include <memory>
#include <vector>

class HittableList : public Hittable{
    public:
        //default constructor
        HittableList();

        /*
        constructor

        input:
            object: a hittable object to assign with initialization
        */
        HittableList(std::shared_ptr<Hittable> object);

        //remove all objects from this HittableList
        //memory used to store this HittableList will also be deallocated
        void clear();

        /*
        add an object to the end of HittableList's object vector
        */
        void add(std::shared_ptr<Hittable> object);

        /*
        hit override used in world scope to find if any rays are contacting any
        Hittable objects

        input:
            r: a ray the renderer is evaluating
            ray_tmin: lower bound of viable hit interval
            ray_tmax: upper bound of viable hit interval
            rec: HitRecord for ray and individual object interaction

        output:
            True if this ray has hit an object in world, else returns false.
        */
        bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override;

    private:
        //the list of objects in world
        std::vector<std::shared_ptr<Hittable>> objects;
};

#endif