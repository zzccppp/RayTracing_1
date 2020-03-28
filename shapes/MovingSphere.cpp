//
// Created by ZZDirty on 2020/3/25.
//

#include "MovingSphere.h"

#include <utility>

bool MovingSphere::hit(const Ray &r, float t_min, float t_max, hit_record &rec) const {
    glm::vec3 oc = r.origin() - center(r.time());
    auto a = glm::dot(r.direction(), r.direction());
    auto half_b = dot(oc, r.direction());
    auto c = glm::dot(oc, oc) - radius * radius;

    auto discriminant = half_b * half_b - a * c;

    if (discriminant > 0) {
        auto root = sqrt(discriminant);

        auto temp = (-half_b - root) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            glm::vec3 outward_normal = (rec.p - center(r.time())) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }

        temp = (-half_b + root) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            glm::vec3 outward_normal = (rec.p - center(r.time())) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;

    return false;
}

MovingSphere::MovingSphere() {}

MovingSphere::MovingSphere(const glm::vec3 &center0, const glm::vec3 &center1, float time0, float time1,
                           float radius, std::shared_ptr<Material> matPtr) : center0(center0), center1(center1),
                                                                             time0(time0), time1(time1),
                                                                             radius(radius),
                                                                             mat_ptr(std::move(matPtr)) {}

glm::vec3 MovingSphere::center(float time) const {
    return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}
