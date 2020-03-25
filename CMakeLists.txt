cmake_minimum_required(VERSION 3.15)
project(RayTracing_1)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pg")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")

include_directories(D:/Library/glm-0.9.9.6/glm/glm)

aux_source_directory(. SRC_FILES)

file(GLOB SRC_SHAPES shapes/**)

file(GLOB SRC_CORE core/**)

add_executable(RayTracing_1 ${SRC_FILES} ${SRC_SHAPES} ${SRC_CORE})