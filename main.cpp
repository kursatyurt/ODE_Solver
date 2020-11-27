 #include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include "eeSolver.hpp"

//Function of the ODE 
double ode(double a)
{
     double x;
     x = 9.81 -(1.229*3.14*1.15/(2*100)) * std::pow(a,2)  ; // Insert the ODE here
     return x;
 }    

//
void writeToFile(
	const std::vector<double> &timeSequence, 
	const std::vector<double> &y_values)
{
	


}

int main(int argc, char *argv[])
{
	/************

	***************/

	/*******************
	1. Ask user which method
	*******************/


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

	auto result = pSolver->solve(y0, dt, finaltime);

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
