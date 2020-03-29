//
// Created by ZZDirty on 2020/3/23.
//

#include "Sphere.h"

bool Sphere::hit(const Ray &r, float t_min, float t_max, hit_record &rec) const {
    glm::vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c; //delta of equation

    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius; //法向量是归一化的
            rec.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}

bool Sphere::bounding_box(float t0, float t1, AABB &output_box) const {
    output_box = AABB(
            center - glm::vec3(radius, radius, radius),
            center + glm::vec3(radius, radius, radius));
    return true;
}

glm::vec3 random_in_unit_sphere() {
    glm::vec3 p;
    do {
        p = 2.0f * glm::vec3(random_double(), random_double(), random_double()) - glm::vec3(1, 1, 1);
    } while (glm::dot(p, p) >= 1.0);
    return p;
}
