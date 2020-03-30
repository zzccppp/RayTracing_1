//
// Created by ZZDirty on 2020/3/24.
//

#ifndef RAYTRACING_1_COMMONFUNC_H
#define RAYTRACING_1_COMMONFUNC_H

#include "Camera.h"
#include "../shapes/hittable.h"
#include "../shapes/Material.h"



glm::vec3 color(const Ray &r, hittable *world, int depth);

inline double ffmin(float a, float b) { return a <= b ? a : b; }

inline double ffmax(float a, float b) { return a >= b ? a : b; }


#endif //RAYTRACING_1_COMMONFUNC_H
