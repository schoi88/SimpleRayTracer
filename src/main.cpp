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

    std::shared_ptr<Lambertian> mat_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    std::shared_ptr<Lambertian> mat_center = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    std::shared_ptr<Dielectric> mat_left = std::make_shared<Dielectric>(1.50);
    std::shared_ptr<Dielectric> bubble = std::make_shared<Dielectric>(1.0 / 1.50);
    std::shared_ptr<Metal> mat_right = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

    world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100, mat_ground));
    world.add(std::make_shared<Sphere>(Point3(0, 0, -1.2), 0.5, mat_center));
    world.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, mat_left));
    world.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.4, bubble));
    world.add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, mat_right));

    Camera cam = Camera((16.0 / 9.0), 400, 100, 50);

    cam.render(world);

    return 0;
}
