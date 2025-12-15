import casadi as cs
import numpy as np

opti = cs.Opti("conic")

CasadiOpts = {}
CasadiOpts['error_on_fail'] = False
CasadiOpts['expand'] = True
solver = 'osqp'
SolverOpts = {}
SolverOpts['verbose'] = True
SolverOpts['max_iter'] = 1000

opti.solver(solver, CasadiOpts, SolverOpts)

# Decision variables
x = opti.variable(2, 1)

# Parameters
H = opti.parameter(2, 2)
g = opti.parameter(2, 1)
A = opti.parameter(3, 2)
b = opti.parameter(3, 1)

cost = 0.5*x.T@(H@x) + g.T@x

opti.minimize(cost)
opti.subject_to(A@x >= b)

inputs = [H, g, A, b]
outputs = [x]
F = opti.to_function("solveQP", inputs, outputs)


codegen_opts = {}
codegen_opts['with_mem'] = True
codegen_opts['with_header'] = True
F.generate("solveQP", codegen_opts)


'''Test the QP solver'''
Hessian = np.diag([2, 8])
grad = np.array([-8, -16]).reshape((-1, 1))
A_con = np.array([[1, 1], 
                  [1, 0], 
                  [0, 1]]).reshape((-1, 2))
b_con = np.array([5, 3, 0]).reshape((-1, 1))
sol = F(Hessian, grad, A_con, b_con)

print("Optimal solution: ", sol)