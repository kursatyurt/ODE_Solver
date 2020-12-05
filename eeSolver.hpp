#include "baseSolver.hpp"

class EESolver : public BaseSolver
{
public:
	std::tuple<std::vector<double>, std::vector<double>>
		solve(std::function<double(double, double)> ode, double initialValue, double startTime, double dt, double totalTime);
};
