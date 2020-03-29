//
// Created by ZZDirty on 2020/3/28.
//

#ifndef RAYTRACING_1_AABB_H
#define RAYTRACING_1_AABB_H

#include <glm.hpp>
#include "Ray.h"


class AABB {
public:
    glm::vec3 _min;
    glm::vec3 _max;

    glm::vec3 min() const { return _min; }

    glm::vec3 max() const { return _max; }

    AABB() {}

    AABB(const glm::vec3 &a, const glm::vec3 &b) {
        _min = a;
        _max = b;
    }

    bool hit(const Ray &r, float tmin, float tmax) const;

};

AABB surrounding_box(AABB box0, AABB box1);

#endif //RAYTRACING_1_AABB_H
