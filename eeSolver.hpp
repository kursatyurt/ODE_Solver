#include "baseSolver.hpp"

class EESolver : public BaseSolver
{
public:
	std::tuple<std::vector<double>, std::vector<double>>
		solve(double initialValue, double dt, double totalTime);
};
