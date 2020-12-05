#include "eeSolver.hpp"
#include <cmath>
#include <iostream>
std::tuple<std::vector<double>, std::vector<double>>
EESolver::solve(std::function<double(double, double)> ode, double initialValue, double startTime, double dt, double totalTime)
{
	std::vector<double> outputTimeSequence = {1, 2, 3};
	std::vector<double> outputNumericalSolutionSequence = {1.5, 2.5, 3};

	/***** 
	test functional
	*****/
	std::cout << ode(1, 1) << "\n";

	/*********
	 implementation
	**********/
	// Allocate vector size for output sequences
	outputTimeSequence.resize(static_cast<int>(floor((totalTime - startTime) / dt)+1));
	outputNumericalSolutionSequence.resize(static_cast<int>(floor((totalTime - startTime) / dt)+1));

	// Initialize
	outputNumericalSolutionSequence[0] = ode( initialValue, startTime );
    outputTimeSequence.at(0) = startTime;
	//Solution Loop

	for (int i = 1; i < outputTimeSequence.size() ; i++){
		outputNumericalSolutionSequence.at(i) = outputNumericalSolutionSequence.at(i-1) + dt * ode(outputNumericalSolutionSequence.at(i-1), outputTimeSequence.at(i-1));
        outputTimeSequence.at(i) = outputTimeSequence.at(i-1) + dt;
	}

	return std::make_tuple(outputTimeSequence, outputNumericalSolutionSequence);
}