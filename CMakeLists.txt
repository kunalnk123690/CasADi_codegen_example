cmake_minimum_required(VERSION 3.6)
project(casadi_optimization_codegen)

find_package(Eigen3 REQUIRED)
find_package(osqp REQUIRED)

include_directories( include ) 

file(GLOB LIB_FILES lib/*.c)
add_library( LIB_QP ${LIB_FILES} )

file(GLOB SRC_FILES src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} LIB_QP Eigen3::Eigen osqp::osqp)