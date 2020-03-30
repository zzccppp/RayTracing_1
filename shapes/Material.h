//
// Created by ZZDirty on 2020/3/24.
//

#ifndef RAYTRACING_1_MATERIAL_H
#define RAYTRACING_1_MATERIAL_H


#include "../core/Ray.h"
#include "hittable.h"
#include "Sphere.h"
#include "../core/Texture.h"

class Material {
public:
    virtual bool scatter(const Ray &r_in, const hit_record &rec, glm::vec3 &attenuation,
                         Ray &scattered) const = 0;
};

class Lambertian : public Material {
public:
    explicit Lambertian(std::shared_ptr<Texture> a) : albedo(a) {}

    virtual bool scatter(const Ray &r_in, const hit_record &rec,
                         glm::vec3 &attenuation, Ray &scattered) const {
        glm::vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = Ray(rec.p, target - rec.p, r_in.time());
        attenuation = albedo->value(rec.u, rec.v, rec.p);
        return true;
    }

    std::shared_ptr<Texture> albedo;
};

glm::vec3 reflect(const glm::vec3 &v, const glm::vec3 &n);

class Metal : public Material {
public:
    Metal(const glm::vec3 &a, float f) : albedo(a) {
        if (f < 1) fuzz = f; else fuzz = 1;
    }

    virtual bool scatter(const Ray &r_in, const hit_record &rec,
                         glm::vec3 &attenuation, Ray &scattered) const {
        glm::vec3 reflected = reflect(glm::normalize(r_in.direction()), rec.normal);
        scattered = Ray(rec.p, reflected, r_in.time());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

    glm::vec3 albedo;

    float fuzz;
};

bool refract(const glm::vec3 &v, const glm::vec3 &n, float ni_over_nt, glm::vec3 &refracted);

class Dielectric : public Material {
public:
    Dielectric(float ri) : ref_idx(ri) {}

    static float schlick(float cosine, float ref_idx) {
        float r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }

    bool scatter(const Ray &r_in, const hit_record &rec, glm::vec3 &attenuation, Ray &scattered) const override {
        glm::vec3 outward_normal;
        glm::vec3 reflected = reflect(r_in.direction(), rec.normal);
        float ni_over_nt;
        attenuation = glm::vec3(1.0, 1.0, 1.0);
        glm::vec3 refracted;

        float reflect_prob;
        float cosine;

        if (dot(r_in.direction(), rec.normal) > 0) {
            outward_normal = -rec.normal;
            ni_over_nt = ref_idx;
            cosine = ref_idx * dot(r_in.direction(), rec.normal)
                     / r_in.direction().length();
        } else {
            outward_normal = rec.normal;
            ni_over_nt = 1.0 / ref_idx;
            cosine = -dot(r_in.direction(), rec.normal)
                     / r_in.direction().length();
        }

        if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
            reflect_prob = schlick(cosine, ref_idx);
        } else {
            reflect_prob = 1.0;
        }

        if (random_double() < reflect_prob) {
            scattered = Ray(rec.p, reflected, r_in.time());
        } else {
            scattered = Ray(rec.p, refracted, r_in.time());
        }

        return true;
    }

    float ref_idx;
};


#endif //RAYTRACING_1_MATERIAL_H
