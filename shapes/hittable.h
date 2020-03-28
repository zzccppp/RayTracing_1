//
// Created by ZZDirty on 2020/3/23.
//

#ifndef RAYTRACING_1_HITTABLE_H
#define RAYTRACING_1_HITTABLE_H

#include "../core/Ray.h"
#include <memory>

class Material;

struct hit_record {
    float t;
    glm::vec3 p;
    glm::vec3 normal;
    std::shared_ptr<Material> mat_ptr;

    bool front_face;

    float u;
    float v;

    inline void set_face_normal(const Ray &r, const glm::vec3 &outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
public:
    virtual bool hit(const Ray& r,float t_min,float t_max,hit_record& rec) const = 0;
};


#endif //RAYTRACING_1_HITTABLE_H
