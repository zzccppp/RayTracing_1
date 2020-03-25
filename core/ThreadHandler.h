//
// Created by ZZDirty on 2020/3/24.
//

#ifndef RAYTRACING_1_THREADHANDLER_H
#define RAYTRACING_1_THREADHANDLER_H

#include <vector>
#include <thread>
#include <mutex>
#include "tgaimage.h"
#include "Camera.h"
#include "../shapes/HittableList.h"

class ThreadHandler {
public:
    std::vector<TGAImage> results;
    int thread_count;
    int thread_ns;
    Camera cam;
    int nx;
    int ny;
    HittableList world;

    ThreadHandler(int threadCount, int threadNs, const Camera &cam, int nx, int ny, const HittableList &world);

    void run();

    static void compute(Camera* cam, int nx, int ny, int ns, HittableList *world, TGAImage *image, int thread_num);

};


#endif //RAYTRACING_1_THREADHANDLER_H
