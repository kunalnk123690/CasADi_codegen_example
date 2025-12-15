cmake_minimum_required(VERSION 3.16)
project(casadi_optimization_codegen)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")
set(CMAKE_BUILD_TYPE Release)

find_package(Eigen3 REQUIRED)
find_package(Python3 REQUIRED COMPONENTS Interpreter)

# --- Get CasADi python package path into a CMake variable ---
execute_process(
    COMMAND ${Python3_EXECUTABLE} -c
            "import casadi, os; print(os.path.dirname(casadi.__file__))"
    OUTPUT_VARIABLE CASADI_PKG_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE _casadi_rc
    ERROR_VARIABLE _casadi_err
)

if(NOT _casadi_rc EQUAL 0 OR CASADI_PKG_PATH STREQUAL "")
    message(FATAL_ERROR
        "Failed to locate CasADi python package path.\n"
        "Python: ${Python3_EXECUTABLE}\n"
        "Error: ${_casadi_err}\n"
        "Tip: ensure CasADi is installed for this Python (python3 -c \"import casadi\")."
    )
endif()

message(STATUS "CASADI_PKG_PATH: ${CASADI_PKG_PATH}")

# If CasADi libs/includes are under the python package directory, keep these.
# (You may need to adjust if your casadi .so/.a lives elsewhere.)
find_library(OSQP_LIBRARY
    NAMES osqp libosqp
    PATHS ${CASADI_PKG_PATH}
    NO_DEFAULT_PATH
)

find_library(CASADI_LIBRARY
    NAMES casadi libcasadi
    PATHS ${CASADI_PKG_PATH}
    NO_DEFAULT_PATH
)

include_directories(
    include
    ${CASADI_PKG_PATH}/include
)

file(GLOB LIB_FILES lib/*.c)
add_library(LIB_QP ${LIB_FILES})

file(GLOB SRC_FILES src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME}
    LIB_QP
    Eigen3::Eigen
    ${OSQP_LIBRARY}
    ${CASADI_LIBRARY}
)
