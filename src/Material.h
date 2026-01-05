/**
 * This is the materials header file. It contains an abstraction for material 
 * classes and also contains its inheriting classes. The main job of materials
 * is to define how light rays behave with hittable objects. Some materials may 
 * reflect or refract light in varying amounts influencing how they appear in the
 * rendered image. These classes will be implemented here comprehensively. 
*/
#ifndef MATERIAL_H
#define MATERIAL_H

#include "Hittable.h"
#include "Color.h"

/*
The abstraction for different material types.
*/
class Material{
    public:
        virtual ~Material() = default;

        virtual bool scatter(const Ray& r_in, const HitRecord& rec, 
                             Color& attenuation, Ray& scattered) const{
            return false;
        }
};

/*
The implementation for lambertian materials.
This type is for materials of matte colors where there is a probability for light
to scatter off of or absorb into the material depending on its attenuation
defined as a color. 
*/
class Lambertian : public Material{
    public:
        Lambertian(const Color& albedo) : albedo(albedo){}

        bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation,
                     Ray& scattered) const override{
            Vec3 scatter_direction = rec.normal + randomUnitVector();

            if(scatter_direction.nearZero()){
                scatter_direction = rec.normal;
            }

            scattered = Ray(rec.p, scatter_direction);
            attenuation = albedo;
            return true;
        }
    private:
        Color albedo;
};

class Metal : public Material{
    public:
        Metal(const Color& albedo, double fuzz) : albedo(albedo), 
              fuzz(fuzz < 1 ? fuzz : 1){}

        bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation,
                     Ray& scattered) const override{
            Vec3 reflected = reflect(r_in.direction(), rec.normal);
            reflected = unitVector(reflected) + (fuzz * randomUnitVector());
            scattered = Ray(rec.p, reflected);
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }
    
    private:
        Color albedo;
        double fuzz;
};

#endif