## Description:
This repository shows how to generate C-code using CasADi (https://web.casadi.org/docs/) toolbox. In this example, C code of a function that solves a simple two dimensional constrained Quadratic Program (QP) with OSQP solver is generated using Python with casadi Opti framework. The repository uses binaries from casadi python wheels.

## Without Docker:
First, install Eigen
```
sudo apt install libeigen3-dev
```
and CasADi
```
pip install casadi
```
Once installed, start with the Python script in the scripts folder. It will generate C source and header files of the QP solver function.

The QP is of the form: 
```math
\min_{\displaystyle x}~~~ \frac{1}{2}x^{T}Hx + g^{T}x
```
```math
\text{Subject to}~~~ Ax \leq b
```
with $H$, $g$, $A$, $b$ being input parameters to the generated function. Once the source and header are generated, put the source in the /lib directory and header in the /include directory. Then build the code using CMake:
```
mkdir build && cd build
cd build
make -j$(nproc)
```

## With Docker:
Run the script `run_docker.sh`. It will build the docker image. Navigate to `/home/codegen/codegen_ws` and follow the same instructions of building using CMake (The docker image has CMake installed).