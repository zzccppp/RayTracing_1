//
// Created by ZZDirty on 2020/3/23.
//

#ifndef RAYTRACING_1_RAY_H
#define RAYTRACING_1_RAY_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Ray {
public:
    glm::vec3 A;
    glm::vec3 B;
    float tm;

    Ray(const glm::vec3 &origin, const glm::vec3 &direction, float time = 0.0f);

    glm::vec3 origin() const { return A; }

    glm::vec3 direction() const { return B; }

    glm::vec3 point_at_parameter(float t) const { return A + t * B; }

    float time() const { return tm; }

    Ray() = default;
};


#endif //RAYTRACING_1_RAY_H
