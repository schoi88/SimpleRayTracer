/**
 * This is the main class driving the ray tracer.
 * Later this will output a gorgeous ray traced scene of various spheres
 * and will include some practices from my time in Operating Systems to
 * hopefully improve the performance of the program. :)
*/

#include "Camera.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Material.h"

int main(){
    HittableList world;

    std::shared_ptr<Lambertian> ground_material = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_material));
    
    for(int a = -11; a < 11; a++){
        for(int b = -11; b < 11; b++){
            double choose_mat = randomDouble();
            Point3 center = Point3(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());

            if((center - Point3(4, 0.2, 0)).length() > 0.9){
                std::shared_ptr<Material> sphere_mat;

                if(choose_mat < 0.8){
                    //make random sphere matte material
                    Color albedo = Color::random() * Color::random();
                    sphere_mat = std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_mat));
                }else if(choose_mat < 0.95){
                    //make random sphere metal material
                    Color albedo = Color::random(0.5, 1);
                    double fuzz = randomDouble(0, 0.5);
                    sphere_mat = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_mat));
                }else{
                    //make random sphere glass material
                    sphere_mat = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_mat));
                }
            }
        }
    }

    std::shared_ptr<Dielectric> mat1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, mat1));

    std::shared_ptr<Lambertian> mat2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, mat2));

    std::shared_ptr<Metal> mat3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, mat3));

    Camera cam = Camera((16.0 / 9.0), 1200, 10, 50, 20, Point3(13, 2, 3), Point3(0, 0, 0), Vec3(0, 1, 0), 0.6, 10.0);
    cam.render(world);

    return 0;
}
