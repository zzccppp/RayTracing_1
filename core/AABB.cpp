//
// Created by ZZDirty on 2020/3/28.
//

#include "AABB.h"
#include "../core/CommonFunc.h"

AABB surrounding_box(AABB box0, AABB box1) {
    glm::vec3 small(ffmin(box0.min().x, box1.min().x),
                    ffmin(box0.min().y, box1.min().y),
                    ffmin(box0.min().z, box1.min().z));
    glm::vec3 big(ffmax(box0.max().x, box1.max().x),
                  ffmax(box0.max().y, box1.max().y),
                  ffmax(box0.max().z, box1.max().z));
    return AABB(small, big);
}

bool AABB::hit(const Ray &r, float tmin, float tmax) const {
    for (int a = 0; a < 3; a++) {
        auto invD = 1.0f / r.direction()[a];
        auto t0 = (min()[a] - r.origin()[a]) * invD;
        auto t1 = (max()[a] - r.origin()[a]) * invD;
        if (invD < 0.0f)
            std::swap(t0, t1);
        tmin = t0 > tmin ? t0 : tmin;
        tmax = t1 < tmax ? t1 : tmax;
        if (tmax <= tmin)
            return false;
    }
    return true;
}
