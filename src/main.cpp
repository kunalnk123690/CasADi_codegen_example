#include <iostream>
#include <Eigen/Dense>
#include "solveQP.h"
#include <vector>
#include <chrono>

using namespace std;

int main()
{

    // Variables
    Eigen::Matrix<double, 2, 1> x;
    
    // Parameters
    Eigen::Matrix<double, 2, 2> H;
    Eigen::Matrix<double, 2, 1> g;
    Eigen::Matrix<double, 3, 2> A;
    Eigen::Matrix<double, 3, 1> b;

    /* Initialize inputs */
    x.setZero();
    H << 2, 0, 
         0, 8;
    g << -8, -16;
    A << 1, 1, 
         1, 0, 
         0, 1;
    b << 5, 3, 0;

    /* Get sizes of the required work vectors (generated function won't work without this) */
    casadi_int sz_arg, sz_res, sz_iw, sz_w;
    solveQP_work(&sz_arg, &sz_res, &sz_iw, &sz_w);
    cout << "Work vector sizes:\n";
    cout << "sz_arg: " << sz_arg << " sz_res: " << sz_res << " sz_iw: " << sz_iw << " sz_w: " << sz_w << "\n";

    /* Allocate input/output buffers and work vectors*/
    const double *arg[sz_arg];
    double *res[sz_res];
    casadi_int iw[sz_iw];
    double w[sz_w];
    
    /* Assign Eigen matrices to imputs and outputs */
    arg[0] = H.data();
    arg[1] = g.data();
    arg[2] = A.data();
    arg[3] = b.data();

    res[0] = x.data();
    int mem = solveQP_checkout();

     auto start = std::chrono::high_resolution_clock::now();
    /* Solve the QP */
    solveQP(arg, res, iw, w, mem);
    auto stop = std::chrono::high_resolution_clock::now();

    /* Display the result */
    cout << "Solution: \n";
    cout << "x = ";
    cout << "[" << x.transpose() << "]\n";

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
    cout << "Computation time (mu-s): " << duration.count() << "\n";


}