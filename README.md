# ODE Solver Project 


This project is an additional part of the **Advanced Programming (IN1503)** course. The project consists of 3 sprints, in each sprint a the code will evolve and gain more futures.


# Sprint 1 Features
1. Layout (completed)
2. Read user method input (completed )
3. Explicit Euler Method (completed)
4. Write results to file (completed) 
5. Read ODE Function From User (to do)

# Sprint 2 Features
1. Implicit Euler Method (Completed)
2. Runge-Kutta 4 Method (Completed)
3. Added A Guide to How to Implement Your New Solver (Completed) 

# Sprint 3 Features

1. Outputs are in Scientific Format
2. Timing for sections added
3. A new writeToFile Function is added
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


# How To Implement New Solver?

First thing you might need a header file the easiest way is just copy an existing solver.
**Don't forget to change the name of the solver.**

Second thing is you need a implementation file. Since we are using same base solver you can pick a closest implementation or Explicit Euler Solver since it is simplest solver. 

- Change header file from euler to your solver
- Change solver name 
- Delete implementation details of Explicit Euler Solver
- Implement your own version of solver
- Add your solver to CmakeLists.txt as shown below

```
add_executable(ode_solver			
"./main.cpp"
"./eeSolver.cpp"
"./ieSolver.cpp"
"./rk4Solver.cpp"
"./yourSolver.cpp"
)
```

- Rebuild the program and enjoy

# Performance Measuring and Improvements


For timestep of 1e-5 and Explicit Euler solver we have observed that only  7 to 20 percent of total execution time used in computation and 90 to 80 percent of total time is spent while writing to file. We have and obvious problem that writing to file is took really huge percentage of the total execution time used. To handle this one we have implemented a new version of writeToFile function called writeToFilev2 it takes same arguments as an input. This new function reduces function time to 1/5th of original one. To total runtime was reduced to 1/4th of original one. 

Using timestep of 1e-5 
Method| Old Runtime (ms) | New Runtime (ms)  | Speedup (Before/After)
----- | ------ | --------------  | ---------------------- 
Explicit Euler  | 580  | 2321    | 4
Implicit Euler	| 1117  | 3059  | 2.7
RK -4 | 732   | 2637   | 3.6


