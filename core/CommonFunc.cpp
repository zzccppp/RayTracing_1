//
// Created by ZZDirty on 2020/3/24.
//

#include "CommonFunc.h"

glm::vec3 color(const Ray &r, hittable *world, int depth) {
    hit_record rec;
    if (world->hit(r, 0.001, std::numeric_limits<float>::max(), rec)) {
        Ray scattered;
        glm::vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth + 1);
        } else {
            return glm::vec3(0, 0, 0);
        }
    } else {
        glm::vec3 unit_direction = glm::normalize(r.direction());
        float t = 0.5 * (unit_direction.y + 1.0);
        return (1.0f - t) * glm::vec3(1.0, 1.0, 1.0) + t * glm::vec3(0.5, 0.7, 1.0);
    }
}
