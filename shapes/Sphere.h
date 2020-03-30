//
// Created by ZZDirty on 2020/3/23.
//

#ifndef RAYTRACING_1_SPHERE_H
#define RAYTRACING_1_SPHERE_H

#include "hittable.h"
#include "../core/Camera.h"
#include <memory>
#include <utility>

class Sphere : public hittable {
public:
    Sphere() {}

    Sphere(glm::vec3 center, float r, std::shared_ptr<Material> m) : center(center), radius(r),
                                                                     mat_ptr(std::move(m)) {};

    virtual bool hit(const Ray &r, float tmin, float tmax, hit_record &rec) const;

    bool bounding_box(float t0, float t1, AABB &output_box) const override;

    static void get_sphere_uv(const glm::vec3 &p, float &u, float &v) {
        auto phi = atan2(p.z, p.x);
        auto theta = asin(p.y);
        u = 1 - (phi + M_PI) / (2 * M_PI);
        v = (theta + M_PI / 2) / M_PI;
    }

    glm::vec3 center;
    float radius;
    std::shared_ptr<Material> mat_ptr;
};

glm::vec3 random_in_unit_sphere();


#endif //RAYTRACING_1_SPHERE_H
