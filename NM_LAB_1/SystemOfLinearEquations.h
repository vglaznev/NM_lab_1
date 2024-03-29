#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Random.h"

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

	void outputToStream(std::ostream&,const bool&);
public:
	SystemOfLinearEquations();

	void inputFromFile();
	void outputToFile(const std::string&);
	void outputToConsole();
	
	std::vector<int> generate(const int&, const int&);
	std::vector<double> solve();
};

