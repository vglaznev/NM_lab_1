#include <iostream>
#include <vector>
#include "SystemOfLinearEquations.h"

int main()
{
	SystemOfLinearEquations default_example;
	std::vector<double> result;
	result = std::move(default_example.solve());
	for (double it : result) {
		std::cout << it << '\t';
	}
}
