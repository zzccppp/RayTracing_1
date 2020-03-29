//
// Created by ZZDirty on 2020/3/28.
//

#ifndef RAYTRACING_1_BVH_H
#define RAYTRACING_1_BVH_H

#include <iostream>
#include "CommonFunc.h"
#include "../shapes/HittableList.h"

class BVH : public hittable {
public:
    std::shared_ptr<hittable> left;
    std::shared_ptr<hittable> right;
    AABB box;

    BVH() = default;

    BVH(HittableList &list, double time0, double time1)
            : BVH(list.objects, 0, list.objects.size(), time0, time1) {}

    BVH(std::vector<std::shared_ptr<hittable>> &objects, size_t start, size_t end, double time0, double time1);

    bool hit(const Ray &r, float t_min, float t_max, hit_record &rec) const override;

    bool bounding_box(float t0, float t1, AABB &output_box) const override;
};

inline bool box_compare(const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b, int axis) {
    AABB box_a;
    AABB box_b;

    if (!a->bounding_box(0, 0, box_a) || !b->bounding_box(0, 0, box_b))
        std::cerr << "No bounding box in bvh_node constructor.\n";

    return box_a.min()[axis] < box_b.min()[axis];
}


inline bool box_x_compare(const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b) {
    return box_compare(a, b, 0);
}

inline bool box_y_compare(const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b) {
    return box_compare(a, b, 1);
}

inline bool box_z_compare(const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b) {
    return box_compare(a, b, 2);
}


#endif //RAYTRACING_1_BVH_H
