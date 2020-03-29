//
// Created by ZZDirty on 2020/3/23.
//

#include "HittableList.h"

bool HittableList::hit(const Ray &r, float t_min, float t_max, hit_record &rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;

    for (const auto &object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

bool HittableList::bounding_box(float t0, float t1, AABB &output_box) const {
    if (objects.empty()) return false;
    AABB temp_box;
    bool first_true = objects[0]->bounding_box(t0, t1, temp_box);

    if (!first_true) return false;

    output_box = temp_box;

    for (const auto &object : objects) {
        if (!object->bounding_box(t0, t1, temp_box))
            return false;
        output_box = surrounding_box(output_box, temp_box);
    }
    return true;
}
