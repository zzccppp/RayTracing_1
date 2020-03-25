//
// Created by ZZDirty on 2020/3/23.
//

#include "Ray.h"

Ray::Ray(const glm::vec3 &origin, const glm::vec3 &direction, float time) : A(origin), B(direction), tm(time) {}
