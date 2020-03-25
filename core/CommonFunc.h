//
// Created by ZZDirty on 2020/3/24.
//

#ifndef RAYTRACING_1_COMMONFUNC_H
#define RAYTRACING_1_COMMONFUNC_H

#include "Camera.h"
#include "../shapes/hittable.h"
#include "../shapes/Material.h"

inline glm::vec3 random() {
    return glm::vec3(random_double(), random_double(), random_double());
}

inline glm::vec3 random(double min, double max) {
    return glm::vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

glm::vec3 color(const Ray &r, hittable *world, int depth);


#endif //RAYTRACING_1_COMMONFUNC_H
