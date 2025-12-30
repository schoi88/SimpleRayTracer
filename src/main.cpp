/**
 * This is the main class driving the ray tracer.
 * Later this will output a gorgeous ray traced scene of various spheres
 * and will include some practices from my time in Operating Systems to
 * hopefully improve the performance of the program. :)
*/

#include "Camera.h"
#include "Color.h"
#include "HittableList.h"
#include "Sphere.h"

int main(){
    HittableList world;

    world.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    Camera cam = Camera((16.0 / 9.0), 400);

    cam.render(world);

    return 0;
}
