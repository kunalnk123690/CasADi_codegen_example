clear; close all; clc

import casadi.*

opti = Opti('conic');

% variables
x = opti.variable(2, 1);

% Parameters
H = opti.parameter(2, 2);
g = opti.parameter(2, 1);
A = opti.parameter(3, 2);
b = opti.parameter(3, 1);

cost = 0.5*x'*H*x + g'*x;

opti.minimize( cost )
opti.subject_to( A*x >= b )

opts = struct;
opts.print_time = false;
opts.verbose = false;
opts.expand = true;
opti.solver('osqp', opts)

F = opti.to_function('solveQP', {H, g, A, b}, {x});

codegen_opts = struct;
codegen_opts.with_mem = true;
codegen_opts.with_header = true;
F.generate('solveQP.c', codegen_opts)

% Test the generated function
Hessian = diag([2 8]);
grad = [-8 -16]';
A_con = [1, 1; 1, 0; 0, 1];
b_con = [5, 3, 0]';
sol = full(F(Hessian, grad, A_con, b_con))