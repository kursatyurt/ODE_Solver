# pragma once
#include "baseSolver.hpp"
class rk4Solver : public BaseSolver
{
public:
	std::tuple<std::vector<double>, std::vector<double>>
		solve(std::function<double(double, double)> ode, double initialValue, double startTime, double dt, double totalTime);
};
