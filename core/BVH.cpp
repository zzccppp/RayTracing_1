//
// Created by ZZDirty on 2020/3/28.
//

#include <algorithm>
#include "BVH.h"

bool BVH::hit(const Ray &r, float t_min, float t_max, hit_record &rec) const {
    if (!box.hit(r, t_min, t_max))
        return false;

    bool hit_left = left->hit(r, t_min, t_max, rec);
    bool hit_right = right->hit(r, t_min, hit_left ? rec.t : t_max, rec);

    return hit_left || hit_right;
}

bool BVH::bounding_box(float t0, float t1, AABB &output_box) const {
    output_box = box;
    return true;
}

BVH::BVH(std::vector<std::shared_ptr<hittable>> &objects, size_t start, size_t end, double time0, double time1) {
    int axis = random_int(0, 2);

    auto comparator = (axis == 0) ? box_x_compare
                                  : (axis == 1) ? box_y_compare
                                                : box_z_compare;

    size_t object_span = end - start;

    //递归地建立子树
    if (object_span == 1) {
        //只有一个就复制为左右树叶
        left = right = objects[start];
    } else if (object_span == 2) {
        //两个就左右各一个
        if (comparator(objects[start], objects[start + 1])) {
            left = objects[start];
            right = objects[start + 1];
        } else {
            left = objects[start + 1];
            right = objects[start];
        }
    } else {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        auto mid = start + object_span / 2;
        left = std::make_shared<BVH>(objects, start, mid, time0, time1);
        right = std::make_shared<BVH>(objects, mid, end, time0, time1);
    }

    AABB box_left, box_right;

    if (!left->bounding_box(time0, time1, box_left)
        || !right->bounding_box(time0, time1, box_right))
        std::cerr << "No bounding box in bvh_node constructor.\n";

    box = surrounding_box(box_left, box_right);

}
