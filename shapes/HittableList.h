//
// Created by ZZDirty on 2020/3/23.
//

#ifndef RAYTRACING_1_HITTABLELIST_H
#define RAYTRACING_1_HITTABLELIST_H

#include <utility>
#include <vector>
#include <memory>
#include "hittable.h"

class HittableList : public hittable {
public:
    std::vector<std::shared_ptr<hittable>> objects;

    HittableList() = default;

    explicit HittableList(std::shared_ptr<hittable> object) {
        add(std::move(object));
    }

    inline void clear() { objects.clear(); }

    inline void add(std::shared_ptr<hittable> object) { objects.push_back(object); }

    virtual bool hit(const Ray &r, float tmin, float tmax, hit_record &rec) const;


};


#endif //RAYTRACING_1_HITTABLELIST_H
