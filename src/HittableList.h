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
        //the list of objects in world
        std::vector<std::shared_ptr<Hittable>> objects;

        //default constructor
        HittableList(){}

        /*
        constructor

        input:
            object: a hittable object to assign with initialization
        */
        HittableList(std::shared_ptr<Hittable> object){
            add(object);
        }

        //remove all objects from this HittableList
        //memory used to store this HittableList will also be deallocated
        void clear(){
            objects.clear();
        }

        /*
        add an object to the end of HittableList's object vector
        */
        void add(std::shared_ptr<Hittable> object){
            objects.push_back(object);
        }

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
        bool hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec)
                 const override{
            //temporary HitRecord to use values from hit on individual object
            HitRecord temp_rec;
            //has this ray hit any objects?
            bool hit_anything = false;
            /*
            closest upper bound for any objects hit (root value from temp_rec)
            when evaluating a hit on an individual object.
            */
            double closest_so_far = ray_tmax;

            //loop through objects added to world to find any hits
            for(const std::shared_ptr<Hittable> object : objects){
                if(object->hit(r, ray_tmin, closest_so_far, temp_rec)){
                    hit_anything = true;
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                }
            }

            return hit_anything;
        }
};

#endif