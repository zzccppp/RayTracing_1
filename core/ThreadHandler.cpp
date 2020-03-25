//
// Created by ZZDirty on 2020/3/24.
//

#include <iostream>
#include "ThreadHandler.h"
#include "CommonFunc.h"

void ThreadHandler::run() {
    std::vector<std::thread*> ts;

    for (int i = 0; i < thread_count; i++) {
        this->results.emplace_back(nx, ny, 3);
    }
    for (int i = 0; i < thread_count; i++) {
        std::thread* t = new std::thread(ThreadHandler::compute, &cam, nx, ny, thread_ns, &world, &(results[i]), i);
        ts.push_back(t);
    }

    for (int i = 0; i < thread_count; i++) {
        ts[i]->join();
    }

    for (int i = 0; i < thread_count; i++) {
        delete ts[i];
    }

}

void ThreadHandler::compute(Camera *cam, int nx, int ny, int ns, HittableList *world, TGAImage *image, int thread_num) {
    for (int j = ny - 1; j >= 0; j--) {
        std::cerr << "\rScanlines remaining: " << j << " ------" << "thread_" << thread_num;
        for (int i = 0; i < nx; i++) {
            glm::vec3 col(0, 0, 0);

            for (int s = 0; s < ns; s++) {
                float u = float(i + random_double()) / float(nx);
                float v = float(j + random_double()) / float(ny);
                Ray r = cam->get_ray(u, v);
                col += color(r, world, 0);
            }
            col /= float(ns);
            col = glm::vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2])); //伽马校正

            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);

            image->set(i, j, TGAColor(ir, ig, ib, 0));
        }
    }
}

ThreadHandler::ThreadHandler(int threadCount, int threadNs, const Camera &cam, int nx, int ny,
                             const HittableList &world) : thread_count(threadCount), thread_ns(threadNs), cam(cam),
                                                          nx(nx), ny(ny), world(world) {}
