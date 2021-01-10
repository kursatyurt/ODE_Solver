 #include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include <fstream>
#include <cmath>
#include "eeSolver.hpp"
#include "ieSolver.hpp"
/********
ODE parameters
***********/
double dt = 0.005; // Step Size for the solver
double startTime = 0; // Solution start Time for the solver
double finaltime = 10; // Final Time for the solver
double y_0 = 1.0; // initial value

/********
Function of the ODE 
***********/
double ode(double y, double t)
{
     double ydot;
	 ydot = (1.0 - y/10.0) * y; // Insert the ODE here
     return ydot;
 }    

/********
Analytic solution of the corresponding ode
***********/
double analytic_sol(double t0, double t)
{
	double y;
	y = 10.0 / (1. + exp(-(t-t0)) * 9.0);
	return y;
}

/********
writeToFile
***********/
void writeToFile(
	const std::vector<double> &timeSequence, 
	const std::vector<double> &y_values)
{
    // Open the results file
    std::ofstream outputFile("results.csv");
	if (!outputFile.is_open())
	{
		throw std::exception("write to file fail");
		return;
	}

    //Write the header
	outputFile << "Time, y value\n" ;   

    for (int i=0; i < timeSequence.size() ; i++){
        outputFile << timeSequence.at(i) << " , " << y_values.at(i) << std::endl;
	}

    // Close the file
    outputFile.close();	
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

	int method(1);
	std::cin >> method;
	/**
	Sanitize the input
	**/
	if (method < 1 || method > 3) {
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
	std::unique_ptr<BaseSolver> pSolver;
	switch (method)
	{
		case 1:
			pSolver = std::make_unique<EESolver>();
			break;
		case 2:
			pSolver = std::make_unique<IESolver>();
			break;
		default:
			pSolver = std::make_unique<EESolver>();
			break;
	}

	if (pSolver == nullptr)
	{
		throw std::exception("no pSolver constructed");
		return -1;
	}
	auto result = pSolver->solve(ode, y_0, startTime, dt, finaltime);

	/*******************
	4. Write to file
	*******************/
	try
	{
		writeToFile(std::get<0>(result), std::get<1>(result));
	}
	catch (const std::exception& e) 
	{
		std::cerr << "catch exception" << e.what() << "\n";
	}
	
	/*******************
	5. Testing: comparing to analytic result
	*******************/
	double err = 0;
	for (int i = 0; i < std::get<0>(result).size(); ++i)
	{
		double time = std::get<0>(result)[i];
		double exact_sol = analytic_sol(startTime,time);
		double y = std::get<1>(result)[i];
		double single_err_term = exact_sol - y;
		single_err_term = single_err_term * single_err_term;
		err += single_err_term;
	}
	err = sqrt(err *(double)dt / (double)finaltime);
	std::cout << "Error is " << err << "\n";

    return 0;
 }
