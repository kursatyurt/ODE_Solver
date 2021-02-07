 #include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include <fstream>
#include <chrono>
#include <cmath>
#include <exception>
#include <iomanip>
#include "eeSolver.hpp"
#include "ieSolver.hpp"
#include "rk4Solver.hpp"
/********
ODE parameters
***********/
double dt = 1e-4; // Step Size for the solver
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
		throw std::runtime_error("Write to file fail");
		return;
	}

    //Write the header
	outputFile << "Time, y value\n" ;   
	std::setprecision(4);

    for (int i=0; i < timeSequence.size()-3 ; i+= 4){
        outputFile << timeSequence[i] << " , " << y_values[i] << std::endl << std::scientific;
        outputFile << timeSequence[i+1] << " , " << y_values[i+1] << std::endl << std::scientific;
        outputFile << timeSequence[i+2] << " , " << y_values[i+2] << std::endl << std::scientific;
        outputFile << timeSequence[i+3] << " , " << y_values[i+3] << std::endl << std::scientific;
	}
//    for (int i=0; i < timeSequence.size() ; i++){
//        outputFile << timeSequence.at(i) << " , " << y_values.at(i) << std::endl;
//	}

    // Close the file
    outputFile.close();	
}

#include <errno.h>
#include <stdio.h>
void writeToFile_v2(
	const std::vector<double> &timeSequence,
	const std::vector<double> &y_values)
{
	// Open the results file
	std::FILE *f;
	errno_t err;
	err = fopen_s(&f, "results.csv", "w");
	if (err != 0)
	{
		throw std::runtime_error("Write to file fail");
		return;
	}

	//Write the header
	std::fprintf(f, "Time, y value\n");
	for (int i=0; i < timeSequence.size() ; i++)
	{
		std::fprintf(f, "%f , %f\n", timeSequence.at(i), y_values.at(i));
	}
	std::fclose(f);
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
		case 3:
			pSolver = std::make_unique<rk4Solver>();
			break;
		default:
			pSolver = std::make_unique<EESolver>();
			break;
	}

	if (pSolver == nullptr)
	{
	//	throw std::exception("no pSolver constructed");
		return -1;
	}

//Setup Timing
	std::chrono::time_point<std::chrono::system_clock> start;
	std::chrono::time_point<std::chrono::system_clock> end;

	start = std::chrono::system_clock::now();
// Get Result
	auto result = pSolver->solve(ode, y_0, startTime, dt, finaltime);

// Print Timing
	end = std::chrono::system_clock::now();
	auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Elapsed time in solver:" << elapsed_time.count() << "ms" << std::endl;
	/*******************
	4. Write to file
	*******************/
	start = std::chrono::system_clock::now();
	try
	{
		writeToFile_v2(std::get<0>(result), std::get<1>(result));
	}
	catch (const std::exception& e) 
	{
		std::cerr << "catch exception" << e.what() << "\n";
	}
	end = std::chrono::system_clock::now();
	elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Elapsed time in file writing:" << elapsed_time.count() << "ms" << std::endl;
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
	std::cout<< "Error is "  << std::scientific<< std::setprecision(3) << err << "\n" ;
    return 0;
 }
