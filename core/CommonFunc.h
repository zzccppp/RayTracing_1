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

//两个不带nan检查的快速min，max类
inline double ffmin(float a, float b) { return a <= b ? a : b; }

inline double ffmax(float a, float b) { return a >= b ? a : b; }

inline int random_int(int min, int max) {
    // Returns a random integer in [min,max].
    return static_cast<int>(random_double(min, max + 1));
}

#endif //RAYTRACING_1_COMMONFUNC_H
