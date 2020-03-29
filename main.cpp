#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"
#include "stb_image.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <limits>


#include "core/Ray.h"
#include "shapes/hittable.h"
#include "shapes/Sphere.h"
#include "shapes/HittableList.h"
#include "core/Camera.h"
#include "shapes/Material.h"
#include "core/CommonFunc.h"
#include "core/tgaimage.h"
#include "core/ThreadHandler.h"
#include "shapes/MovingSphere.h"
#include "core/BVH.h"

HittableList random_scene() {
    HittableList world;

    world.add(std::make_shared<Sphere>(
            glm::vec3(0, -1000, 0), 1000.0f, std::make_shared<Lambertian>(glm::vec3(0.5, 0.5, 0.5))));

    for (int a = -9; a < 9; a++) {
        for (int b = -9; b < 9; b++) {
            auto choose_mat = random_double();
            glm::vec3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());
            if (glm::length(center - glm::vec3(4, 0.2, 0)) > 0.9) {
                if (choose_mat < 0.8) {
                    // diffuse
                    glm::vec3 albedo = random() * random();
                    world.add(
                            std::make_shared<MovingSphere>(center, center + glm::vec3(0, random_double(0, .5), 0), 0.0,
                                                           1.0, 0.2, std::make_shared<Lambertian>(albedo)));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = random(.5, 1);
                    auto fuzz = random_double(0, .5);
                    world.add(
                            std::make_shared<Sphere>(center, 0.2, std::make_shared<Metal>(albedo, fuzz)));
                } else {
                    // glass
                    world.add(std::make_shared<Sphere>(center, 0.2, std::make_shared<Dielectric>(1.5)));
                }
            }
        }
    }

    world.add(std::make_shared<Sphere>(glm::vec3(0, 1, 0), 1.0, std::make_shared<Dielectric>(1.5)));

    world.add(
            std::make_shared<Sphere>(glm::vec3(-4, 1, 0), 1.0, std::make_shared<Lambertian>(glm::vec3(0.4, 0.2, 0.1))));

    world.add(
            std::make_shared<Sphere>(glm::vec3(4, 1, 0), 1.0, std::make_shared<Metal>(glm::vec3(0.7, 0.6, 0.5), 0.0)));

    return world;
}

int main() {
    int nx = 400;
    int ny = 200;
    int ns = 100;

    TGAImage image(nx, ny, 3);

//    std::stringstream ss;
//
//    ss << "P3\n" << nx << " " << ny << "\n255\n";

    HittableList world = random_scene();
    BVH tree(world, 0.0, 1.0);

    const auto aspect_ratio = double(nx) / ny;
    glm::vec3 lookfrom(13, 2, 3);
    glm::vec3 lookat(0, 0, 0);
    glm::vec3 vup(0, 1, 0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.0;


    Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);


    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

            glm::vec3 col(0, 0, 0);

            for (int s = 0; s < ns; s++) { // 通过多采样来实现抗锯齿
                float u = float(i + random_double()) / float(nx);
                float v = float(j + random_double()) / float(ny);
                Ray r = cam.get_ray(u, v);
                col += color(r, &tree, 0);
            }
            col /= float(ns);
            col = glm::vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2])); //伽马校正

            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);

            image.set(i, j, TGAColor(ir, ig, ib, 0));
            //ss << ir << " " << ig << " " << ib << "\n";
        }
    }
//    std::string ppm_string = ss.str();
//
//    std::cout << ppm_string;

/*
    int thread_count = 2;

    ThreadHandler th(thread_count, 1, cam, nx, ny, world);
    th.run();
    image = th.results[0];
    for (int i = 1; i < thread_count; i++) {
        for (int j = ny - 1; j >= 0; j--) {
            for (int i = 0; i < nx; i++) {
                TGAColor c((th.results[i].get(i, j).r + image.get(i, j).r) / 2,
                           (th.results[i].get(i, j).g + image.get(i, j).g) / 2,
                           (th.results[i].get(i, j).b + image.get(i, j).b) / 2, 0);
                image.set(i, j, c);
            }
        }
    }
     */
    image.flip_vertically();
    image.write_tga_file("output22.tga");
}