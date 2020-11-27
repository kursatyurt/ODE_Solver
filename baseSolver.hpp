#include <memory>
#include <string>
#include <tuple>
#include <vector>
#include <functional>
class BaseSolver
{
public:
	virtual ~BaseSolver() {};
	virtual std::tuple<std::vector<double>, std::vector<double>>
		solve(std::function<double(double,double)> ode, double initialValue, double dt, double totalTime) = 0;
};