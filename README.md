## Description:
This repository shows how to generate C-code using CasADi toolbox (https://web.casadi.org/docs/). In this example, C code of a function that solves a simple two dimensional constrained Quadratic Program (QP) with OSQP solver is generated using CasADi MATLAB interface.
## Using this repository:
First, install Eigen 
```
sudo apt install libeigen3-dev
```
and OSQP on your machine. To build OSQP from source, refer to this link - https://github.com/osqp/osqp.
Once Eigen and OSQP are installed, run the MATLAB script in the scripts folder. It will generate C source and header files for the QP solver function. The QP is of the form:
```math
\min_{\displaystyle x}~~~ \frac{1}{2}x^{T}Hx + g^{T}x
```
```math
\text{Subject to}~~~ Ax \leq b
```
with $H \in \mathbb{R}^{2 \times 2}$, $g \in \mathbb{R}^{2}$, $A \in \mathbb{R}^{3 \times 2}$, $b \in \mathbb{R}^{3}$ being input parameters to the generated function. Once the source and header are generated, put the source in the /lib directory and header in the /include directory. Then build the code using CMake:
```
mkdir build && cd build
cd build
make -j$(nproc)
```