#include "eeSolver.hpp"
#include<cmath>

std::tuple<std::vector<double>, std::vector<double>>
EESolver::solve(double initialValue, double dt, double totalTime)
{
	std::vector<double> outputTimeSequence = {1,2,3};
	std::vector<double> outputNumericalSolutionSequence = {1.5,2.5,3};

	/*********
	 implementation
	**********/
	//double time;
	//std::vector<double> velocity{ 0.0 }; // Solution Vector

	//time = 0.0; // Initialize Time 
	////Solution Loop for Explicit Euler
	//while (time < finaltime)
	//{
	//	double veln = velocity.back() + ode(velocity.back()) * dt;
	//	velocity.push_back(veln);
	//	time += dt;
	//}


	//time = 0.0; //Initialize Time for Output 
	////Output loop that print  Time and Velocity to Screen
	//for (int n : velocity)
	//{
	//	std::cout << time << '\b' << n << '\n';
	//	time += dt;
	//}


	return std::make_tuple(outputTimeSequence, outputNumericalSolutionSequence);
}