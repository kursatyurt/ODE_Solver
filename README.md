# project_ode_solver

This project is an additional part of the Advanced Programming (IN1503) course. The project consists of 3 sprints, in each sprint a the code will evolve and gain more futures.


# Sprint 1 Feature
1. Layout (completed)
2. Read user method input (completed )
3. Explicit Euler Method (completed)
4. Write results to file (completed) 
5. Read ODE Function From User (to do)

# Sprint 2 Feature 
1. Implicit Euler Metho (Completed) 

# Test Environment
1. Linux
2. VS2017

# Build instruction
```
mkdir build
cd build
cmake ..
make
```

# User guide
To use the code, you have to change the corresponding section in the file main.cpp

You may change the parameters in the section ODE parameters
```
/********
ODE parameters
***********/
double dt = 0.005; // Step Size for the solver
double startTime = 0; // Solution start Time for the solver
double finaltime = 10; // Final Time for the solver
double y_0 = 1.0; // initial value
```

You may change the definition of the ode in the section function definition of the ODE
```
/********
Function of the ODE 
***********/
double ode(double y, double t)
{
     double ydot;
	 ydot = (1.0 - y/10.0) * y; // Insert the ODE here
     return ydot;
 }    
```

According, You need to change the analytic solution for result comparison
```
/********
Analytic solution of the corresponding ode
***********/
double analytic_sol(double t0, double t)
{
	double y;
	y = 10.0 / (1. + exp(-(t-t0)) * 9.0);
	return y;
}
```
