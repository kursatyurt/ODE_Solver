#include "ieSolver.hpp"
#include <cmath>
#include <iostream>

std::tuple<bool, double> secant_method(
	std::function<double(double)> G, 
	double initial_guess)
{
	const double epsilon = pow(10, -4);
	const double max_iteration_num = pow(10, 4);

	double diff_guess = 1.;
	
	double current_guess = initial_guess;
	double previous_guess = current_guess + 0.05;
	double next_guess = 1.;

	unsigned current_iter = 0;
	while (abs(diff_guess) > epsilon* abs(current_guess) && current_iter < max_iteration_num)
	{
		next_guess = current_guess - G(current_guess) * (current_guess-previous_guess) / (G(current_guess) - G(previous_guess));
		diff_guess = next_guess - current_guess;
		current_guess = next_guess;
		current_iter = current_iter + 1;
	}
	
	double root = current_guess;
	bool isSolvable = false;
	if (current_iter < max_iteration_num)
	{
		isSolvable = true;
	}
	return std::make_tuple(isSolvable, root);
}



std::tuple<std::vector<double>, std::vector<double>>
IESolver::solve(std::function<double(double, double)> ode, double initialValue, double startTime, double dt, double totalTime)
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

	for (int i = 1; i < outputTimeSequence.size() ; i++)
	{
		outputNumericalSolutionSequence.at(i - 1) + dt * ode(outputNumericalSolutionSequence.at(i - 1), outputTimeSequence.at(i - 1));
		double tmp1 = outputNumericalSolutionSequence.at(i - 1);
		double tmp2 = outputTimeSequence.at(i - 1);
		auto g = [ode,tmp1, tmp2, dt](double y)
		{
			return y - tmp1 - dt * ode(tmp2 + dt, y);
		};

		auto result = secant_method(g,outputNumericalSolutionSequence.at(i - 1));
		if (std::get<0>(result) != true)
		{
			std::cerr << "iterative method fail to converge.\n";
			break;
		}
		outputNumericalSolutionSequence.at(i) = std::get<1>(result);
        outputTimeSequence.at(i) = outputTimeSequence.at(i-1) + dt;
	}

	return std::make_tuple(outputTimeSequence, outputNumericalSolutionSequence);
}