//
// Created by ZZDirty on 2020/3/29.
//

#ifndef RAYTRACING_1_TEXTURE_H
#define RAYTRACING_1_TEXTURE_H

#include "glm.hpp"
#include "Camera.h"
#include <cmath>
#include <memory>

class Texture {
public:
    virtual glm::vec3 value(float u, float v, const glm::vec3 &p) const = 0;
};

class ConstantTexture : public Texture {
public:
    glm::vec3 color;

    ConstantTexture() = default;

    explicit ConstantTexture(glm::vec3 c) : color(c) {}

    glm::vec3 value(float u, float v, const glm::vec3 &p) const override {
        return color;
    }
};

class CheckerTexture : public Texture {
public:
    std::shared_ptr<Texture> odd;
    std::shared_ptr<Texture> even;

    CheckerTexture(std::shared_ptr<Texture> odd, std::shared_ptr<Texture> even);

    CheckerTexture();

    glm::vec3 value(float u, float v, const glm::vec3 &p) const override;
};

class Perlin {
private:
    static const int point_count = 256;
    glm::vec3 *ranvec;
    int *perm_x;
    int *perm_y;
    int *perm_z;

    static int *perlin_generate_perm() {
        auto p = new int[point_count];

        for (int i = 0; i < Perlin::point_count; i++)
            p[i] = i;

        permute(p, point_count);

        return p;
    }

    static void permute(int *p, int n) {
        for (int i = n - 1; i > 0; i--) {
            int target = random_int(0, i);
            int tmp = p[i];
            p[i] = p[target];
            p[target] = tmp;
        }
    }

public:
    Perlin() {
        ranvec = new glm::vec3[point_count];
        for (int i = 0; i < point_count; ++i) {
            ranvec[i] = glm::normalize(random(-1, 1));
        }

        perm_x = perlin_generate_perm();
        perm_y = perlin_generate_perm();
        perm_z = perlin_generate_perm();
    }

    ~Perlin() {
        delete[] ranvec;
        delete[] perm_x;
        delete[] perm_y;
        delete[] perm_z;
    }

    float noise(const glm::vec3 &p) const {
        auto u = p.x - floor(p.x);
        auto v = p.y - floor(p.y);
        auto w = p.z - floor(p.z);
        auto i = static_cast<int>(floor(p.x));
        auto j = static_cast<int>(floor(p.y));
        auto k = static_cast<int>(floor(p.z));
        glm::vec3 c[2][2][2];

        for (int di = 0; di < 2; di++)
            for (int dj = 0; dj < 2; dj++)
                for (int dk = 0; dk < 2; dk++)
                    c[di][dj][dk] = ranvec[
                            perm_x[(i + di) & 255] ^
                            perm_y[(j + dj) & 255] ^
                            perm_z[(k + dk) & 255]
                    ];

        return trilinear_interp(c, u, v, w);
    }

    inline double trilinear_interp(glm::vec3 c[2][2][2], double u, double v, double w) const {
        auto uu = u * u * (3 - 2 * u);
        auto vv = v * v * (3 - 2 * v);
        auto ww = w * w * (3 - 2 * w);
        auto accum = 0.0;

        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                for (int k = 0; k < 2; k++) {
                    glm::vec3 weight_v(u - i, v - j, w - k);
                    accum += (i * uu + (1 - i) * (1 - uu)) *
                             (j * vv + (1 - j) * (1 - vv)) *
                             (k * ww + (1 - k) * (1 - ww)) * glm::dot(c[i][j][k], weight_v);
                }

        return accum;
    }

    float turb(const glm::vec3 &p, int depth = 7) const {
        auto accum = 0.0;
        auto temp_p = p;
        auto weight = 1.0;

        for (int i = 0; i < depth; i++) {
            accum += weight * noise(temp_p);
            weight *= 0.5;
            temp_p *= 2;
        }

        return static_cast<float>(fabs(accum));
    }

};

class NoiseTexture : public Texture {
public:
    Perlin noise;
    float scale = 1.0f;

    NoiseTexture() = default;

    explicit NoiseTexture(float scale) : scale(scale) {}

    glm::vec3 value(float u, float v, const glm::vec3 &p) const override {
        return glm::vec3(1, 1, 1) * 0.5f * static_cast<float>(1 + std::sin(scale * p.z + 10 * noise.turb(p)));
    }


};


class ImageTexture : public Texture {
public:
    unsigned char *data;
    int nx, ny;

    ImageTexture() {
        data = nullptr;
        nx = 0;
        ny = 0;
    }

    ImageTexture(unsigned char *pixels, int A, int B)
            : data(pixels), nx(A), ny(B) {}

    ~ImageTexture() {
        delete data;
    }


    glm::vec3 value(float u, float v, const glm::vec3 &p) const override;
};

#endif //RAYTRACING_1_TEXTURE_H
