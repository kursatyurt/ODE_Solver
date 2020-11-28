 #include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include <cmath>
#include "eeSolver.hpp"

/********
Function of the ODE 
***********/
double ode(double y, double t)
{
     double ydot;
	 ydot = 9.81 -(1.229*3.14*1.15/(2*100)) * std::pow(t,2)  ; // Insert the ODE here
     return ydot;
 }    

/********
writeToFile
***********/
void writeToFile(
	const std::vector<double> &timeSequence, 
	const std::vector<double> &y_values)
{
	


}

/********
main
***********/
int main(int argc, char *argv[])
{
	/*******************
	1. Ask user which method
	*******************/
        std::cout << "Please enter which method would you like to use\n";
	std::cout << "Explicit Euler : 1 , Implicit Euler : 2, RK4 : 3\n";
	std::cout << "Default is Explicit Euler\n";
        int method (1);
	std::cin >> method;
	/**
    Sanitize the input
    **/
    if (method < 1 || method > 3){
		std::cout << "Wrong Choice !!!\n";
		std::cout << "Default method will be used\n";
		method = 1;
	}
	std::cout << "Chosen method is " << method << std::endl;


	/*******************
	2. Ask for ODE (hard code at the beginning)
	*******************/


	/*******************
	3. Compute the numerical vector
	*******************/
	double dt = 0.1; // Step Size for the solver
	double finaltime = 10; // Final Time for the solver
	double y0 = 0; // initial value

	std::shared_ptr<BaseSolver> pSolver(new EESolver());
	if (pSolver == NULL)	
	{
		throw "pSolver new fail";
		return -1;
	}

	auto result = pSolver->solve(ode, y0, dt, finaltime);
	for (int i = 0; i < std::get<0>(result).size(); ++i)
	{
		std::cout << std::get<0>(result)[i] << " " << std::get<1>(result)[i] << "\n";
	}

	/*******************
	4. Write to file
	*******************/
	writeToFile(std::get<0>(result), std::get<1>(result));


    return 0;
 }
