#include "HittableList.h"

HittableList::HittableList(){}

HittableList::HittableList(std::shared_ptr<Hittable> object){
    add(object);
}

void HittableList::clear(){
    objects.clear();
}

void HittableList::add(std::shared_ptr<Hittable> object){
    objects.push_back(object);
}

bool HittableList::hit(const Ray& r, Interval ray_t, HitRecord& rec) const{
    //temporary HitRecord to use values from hit on individual object
    HitRecord temp_rec;
    //has this ray hit any objects?
    bool hit_anything = false;
    /*
    closest upper bound for any objects hit (root value from temp_rec)
    when evaluating a hit on an individual object.
    */
    double closest_so_far = ray_t.max;

    //loop through objects added to world to find any hits
    for(const std::shared_ptr<Hittable> object : objects){
        if(object->hit(r, Interval(ray_t.min, closest_so_far), temp_rec)){
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}
