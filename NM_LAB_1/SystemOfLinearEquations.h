#pragma once
#include <vector>

class SystemOfLinearEquations
{
	std::vector<double> upperDiagonal;
	std::vector<double> diagonal;
	std::vector<double> lowerDiagonal;

	std::vector<double> firstRow;
	std::vector<double> secondRow;

	std::vector<double> freeColumn;

	int sizeOfSystem;
	int posOfFirstRow;

public:
	SystemOfLinearEquations();
	std::vector<double> solve();

};

