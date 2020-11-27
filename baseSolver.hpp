#include <memory>
#include <string>
#include <tuple>
#include <vector>

class BaseSolver
{
public:
	virtual ~BaseSolver() {};
	virtual std::tuple<std::vector<double>, std::vector<double>>
		solve(double initialValue, double dt, double totalTime) = 0;
};