//
// Created by ZZDirty on 2020/3/23.
//

#ifndef RAYTRACING_1_CAMERA_H
#define RAYTRACING_1_CAMERA_H

#include "Ray.h"
#include <functional>
#include <random>

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    static std::function<double()> rand_generator = std::bind(distribution, generator);
    return rand_generator();
}

inline double random_double(float a, float b) {
    static std::uniform_real_distribution<double> distribution(a, b);
    static std::mt19937 generator;
    static std::function<double()> rand_generator = std::bind(distribution, generator);
    return rand_generator();
}

inline glm::vec3 random() {
    return glm::vec3(random_double(), random_double(), random_double());
}

inline glm::vec3 random(double min, double max) {
    return glm::vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

inline int random_int(int min, int max) {
    // Returns a random integer in [min,max].
    return static_cast<int>(random_double(min, max + 1));
}

class Camera {
public:

    static float degrees_to_radians(float deg) {
        return deg / 180 * 3.14159265;
    }

    static glm::vec3 random_in_unit_disk() {
        while (true) {
            glm::vec3 p = glm::vec3((float) random_double(-1, 1), (float) random_double(-1, 1), 0.0f);
            if (glm::dot(p, p) >= 1) continue;
            return p;
        }
    }

    Camera(glm::vec3 lookfrom, glm::vec3 lookat, glm::vec3 vup, float vfov, float aspect,
           float aperture, float focus_dist, float t0 = 0, float t1 = 0) {
        origin = lookfrom;
        lens_radius = aperture / 2;
        time0 = t0;
        time1 = t1;

        float theta = degrees_to_radians(vfov);
        float half_height = tan(theta / 2);
        float half_width = aspect * half_height;

        w = glm::normalize(lookfrom - lookat);
        u = glm::normalize(cross(vup, w));
        v = cross(w, u);
        lower_left_corner = origin
                            - half_width * focus_dist * u
                            - half_height * focus_dist * v
                            - focus_dist * w;

        horizontal = 2 * half_width * focus_dist * u;
        vertical = 2 * half_height * focus_dist * v;
    }

    Ray get_ray(float s, float t) {
        glm::vec3 rd = lens_radius * random_in_unit_disk();
        glm::vec3 offset = u * rd.x + v * rd.y;

        return Ray(
                origin + offset,
                lower_left_corner + s * horizontal + t * vertical - origin - offset,
                random_double(time0, time1)
        );
    }

    glm::vec3 origin;
    glm::vec3 lower_left_corner;
    glm::vec3 horizontal;
    glm::vec3 vertical;
    glm::vec3 u, v, w;
    float lens_radius;
    float time0, time1;
};


#endif //RAYTRACING_1_CAMERA_H
