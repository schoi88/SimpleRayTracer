#include "Camera.h"

Camera::Camera(){}

Camera::Camera(double ar, int iw, int spp, int md){
    aspect_ratio = ar;
    image_width = iw;
    samples_per_pixel = spp;
    max_depth = md;

    //initialize image dimensions
    image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    //set color scale factor for pixel sample sum
    pixel_samples_scale = 1.0 / samples_per_pixel;

    //define camera center;
    center = Point3(0, 0, 0);

    //viewport dimensions
    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * 
        (static_cast<double>(image_width) / image_height);

    //Calculate vectors along horizontal and vertical viewport edges
    Vec3 viewport_u = Vec3(viewport_width, 0, 0);
    Vec3 viewport_v = Vec3(0, -viewport_height, 0);

    //Calculate horizontal and vertical delta vectors between pixels
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    //Calculate location of upper left pixel
    Vec3 viewport_upper_left = center - Vec3(0, 0, focal_length) - 
        viewport_u / 2 - viewport_v / 2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

void Camera::render(const Hittable& world){
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int h = 0; h < image_height; h++){
        for(int w = 0; w < image_width; w++){
            Color pixelColor = Color(0, 0, 0);
            for(int sample = 0; sample < samples_per_pixel; sample++){
                Ray r = getRay(w, h);
                pixelColor += rayColor(r, max_depth, world);
            }
            writeColor(std::cout, pixel_samples_scale * pixelColor);
        }
    }
}

Color Camera::rayColor(const Ray& r, int depth, const Hittable& world) const{
    //if ray bounce depth is exceeded, no more light is gathered
    if(depth <= 0){
        return Color(0, 0, 0);
    }
            
    HitRecord rec;

    //if ray hits an object, it will bounce and retain 50 percent of its color
    if(world.hit(r, Interval(0.001, INF), rec)){
        Vec3 direction = rec.normal + randomUnitVector();
        return 0.1 * rayColor(Ray(rec.p, direction), depth - 1, world);
    }

    //ray has bounced off world with no more hits 
    Vec3 unit_direction = unitVector(r.direction());
    double a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

Ray Camera::getRay(int x, int y) const{
    Vec3 offset = sampleSquare();
    Vec3 pixel_sample = pixel00_loc + ((x + offset.x()) * pixel_delta_u) +
        ((y + offset.y()) * pixel_delta_v);
    
    Point3 ray_origin = center;
    Vec3 ray_direction = pixel_sample - ray_origin;

    return Ray(ray_origin, ray_direction);
}

Vec3 Camera::sampleSquare() const{
    return Vec3(randomDouble() - 0.5, randomDouble() - 0.5, 0);
}