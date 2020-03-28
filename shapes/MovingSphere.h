//
// Created by ZZDirty on 2020/3/25.
//

#ifndef RAYTRACING_1_MOVINGSPHERE_H
#define RAYTRACING_1_MOVINGSPHERE_H

#include "Sphere.h"

class MovingSphere : public hittable {
public:
    glm::vec3 center0, center1;
    float time0, time1;
    float radius;
    std::shared_ptr<Material> mat_ptr;

    bool hit(const Ray &r, float t_min, float t_max, hit_record &rec) const override;

    MovingSphere();

    MovingSphere(const glm::vec3 &center0, const glm::vec3 &center1, float time0, float time1, float radius,
                 std::shared_ptr<Material> matPtr);

    glm::vec3 center(float time) const;

};


#endif //RAYTRACING_1_MOVINGSPHERE_H
