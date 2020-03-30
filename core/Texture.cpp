//
// Created by ZZDirty on 2020/3/29.
//

#include "Texture.h"

#include <utility>

glm::vec3 CheckerTexture::value(float u, float v, const glm::vec3 &p) const {
    auto sins = sin(10 * p.x) * sin(10 * p.y) * sin(10 * p.z);
    if (sins < 0) {
        return odd->value(u, v, p);
    } else {
        return even->value(u, v, p);
    }
}

CheckerTexture::CheckerTexture(std::shared_ptr<Texture> odd, std::shared_ptr<Texture> even) : odd(std::move(odd)),
                                                                                              even(std::move(even)) {}

CheckerTexture::CheckerTexture() {}

glm::vec3 ImageTexture::value(float u, float v, const glm::vec3 &p) const {
    if (data == nullptr)
        return glm::vec3(0, 1, 1);

    auto i = static_cast<int>((u) * nx);
    auto j = static_cast<int>((1 - v) * ny - 0.001);

    if (i < 0) i = 0;
    if (j < 0) j = 0;
    if (i > nx - 1) i = nx - 1;
    if (j > ny - 1) j = ny - 1;

    auto r = static_cast<int>(data[3 * i + 3 * nx * j + 0]) / 255.0;
    auto g = static_cast<int>(data[3 * i + 3 * nx * j + 1]) / 255.0;
    auto b = static_cast<int>(data[3 * i + 3 * nx * j + 2]) / 255.0;

    return glm::vec3(r, g, b);
}
