#include <iostream>
#include <vector>
#include "SystemOfLinearEquations.h"

int main()
{
	/*SystemOfLinearEquations default_example;
	std::vector<double> result;
	result = std::move(default_example.solve());
	for (double it : result) {
		std::cout << it << '\t';
	}*/
	SystemOfLinearEquations default_example;
	std::vector<int> solutionVector = default_example.generate(1,2);

	default_example.outputToConsole();
	std::cout << std::endl;

	std::vector<double> realSolutionVector = default_example.solve();


	std::cout << "\nSolution vector:\n";
	for (int it : solutionVector) {
		std::cout << it << '\t';
	}
	std::cout << "\nReal solution vector:\n";
	for (double it : realSolutionVector) {
		std::cout << it << '\t';
	}
}
