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

class Dielectric : public Material{
    public:
        Dielectric(double refraction_index) : refraction_index(refraction_index){}

        bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, 
                     Ray& scattered) const override{
            attenuation = Color(1.0, 1.0, 1.0);
            double ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;
            Vec3 unit_direction = unitVector(r_in.direction());

            double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
            double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

            bool cannot_refract = ri * sin_theta > 1.0;

            Vec3 direction;
            if(cannot_refract || reflectance(cos_theta, ri) > randomDouble()){
                direction = reflect(unit_direction, rec.normal);
            }else{
                direction = refract(unit_direction, rec.normal, ri);
            }

            scattered = Ray(rec.p, direction);
            return true;
        }
    private:
        //the ratio of the refractive index of the material over the enclosing media
        //shows how much light bends when crossing the material
        double refraction_index;

        static double reflectance(double cosine, double refraction_index){
            double r0 = (1 - refraction_index) / (1 + refraction_index);
            r0 = r0 * r0;
            return r0 + (1 - r0) * std::pow((1 - cosine), 5);
        }
};

#endif