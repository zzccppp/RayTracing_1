//
// Created by ZZDirty on 2020/3/24.
//

#include "Material.h"

glm::vec3 reflect(const glm::vec3 &v, const glm::vec3 &n) {
    return v - 2 * dot(v, n) * n;
}

bool refract(const glm::vec3 &v, const glm::vec3 &n, float ni_over_nt, glm::vec3 &refracted) {
    glm::vec3 uv = glm::normalize(v);
    float dt = dot(uv, n);
    float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);//计算全反射的判别式
    if (discriminant > 0) {
        refracted = ni_over_nt * (uv - n * dt) - n * static_cast<float>(sqrt(discriminant));
        return true;
    } else
        return false;
}
