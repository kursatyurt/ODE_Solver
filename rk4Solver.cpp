#include "rk4Solver.hpp"
#include <cmath>
#include <iostream>
std::tuple<std::vector<double>, std::vector<double>>
rk4Solver::solve(std::function<double(double, double)> ode, double initialValue, double startTime, double dt, double totalTime)
{
	std::vector<double> outputTimeSequence;
	std::vector<double> outputNumericalSolutionSequence;

	/*********
	 implementation
	**********/
	// Allocate vector size for output sequences
	outputTimeSequence.resize(static_cast<int>(floor((totalTime - startTime) / dt)+1));
	outputNumericalSolutionSequence.resize(static_cast<int>(floor((totalTime - startTime) / dt)+1));

	// Initialize
	outputNumericalSolutionSequence[0] = initialValue;
    outputTimeSequence.at(0) = startTime;
	//Solution Loop

	for (int i = 1; i < outputTimeSequence.size() ; i++){
		auto k1 = ode(outputNumericalSolutionSequence.at(i-1), outputTimeSequence.at(i-1));
		auto k2 = ode(outputNumericalSolutionSequence.at(i-1)+dt/2.0d*k1, outputTimeSequence.at(i-1)+dt/2.0d);
		auto k3 = ode(outputNumericalSolutionSequence.at(i-1)+dt/2.0d*k2, outputTimeSequence.at(i-1)+dt/2.0d);
		auto k4 = ode(outputNumericalSolutionSequence.at(i-1)+dt/2.0d*k3, outputTimeSequence.at(i-1)+dt);
		
		
		outputNumericalSolutionSequence.at(i) = outputNumericalSolutionSequence.at(i-1) + dt * 1.0d/6.0d *(k1+2.0d*k2+2.0d*k3+k4) ;
        outputTimeSequence.at(i) = outputTimeSequence.at(i-1) + dt;

	}

	return std::make_tuple(outputTimeSequence, outputNumericalSolutionSequence);
}