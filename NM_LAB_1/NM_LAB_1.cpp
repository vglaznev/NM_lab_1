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
	std::cout << '\n';
	default_example.outputToConsole();
	default_example.outputToFile("D:\\test.txt");
}
