#include "SystemOfLinearEquations.h"

SystemOfLinearEquations::SystemOfLinearEquations() {

	/*std::vector<double> arr_1{ -9, -6, -9, 0, -6, 7, -1, 5, 5 };
	upperDiagonal = arr_1;
	std::vector<double> arr_2{ -2, 9,-9,-5,-1,-4,-9, -5, 2,-5 };
	diagonal = arr_2;
	std::vector<double> arr_3{ -1,-9,-2,-1,8,-6,4,-2, -10 };
	lowerDiagonal = arr_3;
	std::vector<double> arr_4{ -6, 8, -1, 0, -4, 6, -9, -9, -9, -7 };
	firstRow = arr_4;
	std::vector<double> arr_5{ 1, -6, 1, -6, 1, 0, -5, -2, -7, -7 };
	secondRow = arr_5;

	std::vector<double> arr_6{ -11, -4, -50, -42, -9, 18, -26, 3, 3, -15 };
	freeColumn = arr_6;

	sizeOfSystem = 10;
	posOfFirstRow = 2;*/
}


void SystemOfLinearEquations::inputFromFile() {

}
void SystemOfLinearEquations::outputToStream(std::ostream& outStream, const bool& formatFlag) {
	outStream << std::setprecision(3);
	for (int i = 0; i < sizeOfSystem; i++) {
		for (int j = 0; j < sizeOfSystem; j++)
		{
			if (i != posOfFirstRow && i != posOfFirstRow + 1) {
				if (j + i == sizeOfSystem - 2) outStream << upperDiagonal[i] << '\t';
				else if (j + i == sizeOfSystem - 1) outStream << diagonal[i] << '\t';
				else if (j + i == sizeOfSystem) outStream << lowerDiagonal[i - 1] << '\t';
				else outStream << 0 << '\t';
			}
			else if (i == posOfFirstRow) {
				outStream << firstRow[j] << '\t';
			}
			else {
				outStream << secondRow[j] << '\t';
			}
		}
		if (formatFlag) {
			outStream << /*"||\t"*/ "\t" << freeColumn[i];
		}
		outStream << '\n';
	}

	if (!formatFlag) {
		outStream << '\n';
		for (int i = 0; i < sizeOfSystem; i++) {
			outStream << freeColumn[i] << '\n';
		}
	}
	outStream << '\n';
}

void SystemOfLinearEquations::outputToFile(const std::string& path) {
	std::ofstream outputFile;
	outputFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		outputFile.open(path);
		outputToStream(outputFile, false);
		outputFile.close();
	}
	catch (const std::ifstream::failure& fail) {
		std::cerr << "Exception opening/reading/writing input file. \n ";
	}
}
void SystemOfLinearEquations::outputToConsole() {
	outputToStream(std::cout, true);
}

std::vector<int> SystemOfLinearEquations::generate(const int& expOfSysSize, const int& expOfElems) {
	Random newRandom;
	newRandom.randomize();

	std::vector<int> solutionVector;

	sizeOfSystem = newRandom.randomIntOfOrderOfMagnitude(expOfSysSize);
	posOfFirstRow = newRandom.randomInt(0, sizeOfSystem - 2);

	for (int i = 0; i < sizeOfSystem; i++) {
		upperDiagonal.push_back(newRandom.randomDouble(expOfElems));
		diagonal.push_back(newRandom.randomDouble(expOfElems));
		lowerDiagonal.push_back(newRandom.randomDouble(expOfElems));

		firstRow.push_back(newRandom.randomDouble(expOfElems));
		secondRow.push_back(newRandom.randomDouble(expOfElems));

		solutionVector.push_back(newRandom.randomInt(expOfElems));
	}

	lowerDiagonal.pop_back();
	upperDiagonal.pop_back();

	//Fix overlaps

	diagonal[posOfFirstRow] = firstRow[sizeOfSystem - posOfFirstRow - 1];
	diagonal[posOfFirstRow + 1] = secondRow[sizeOfSystem - posOfFirstRow - 2];

	if (posOfFirstRow != 0) lowerDiagonal[posOfFirstRow - 1] = firstRow[sizeOfSystem - posOfFirstRow];
	lowerDiagonal[posOfFirstRow] = secondRow[sizeOfSystem - posOfFirstRow - 1];

	if (posOfFirstRow != sizeOfSystem - 2) upperDiagonal[posOfFirstRow + 1] = secondRow[sizeOfSystem - posOfFirstRow - 3];
	upperDiagonal[posOfFirstRow] = firstRow[sizeOfSystem - posOfFirstRow - 2];

	for (int i = 0; i < sizeOfSystem; i++) {
		double result = 0;

		if (i != posOfFirstRow && i != posOfFirstRow + 1) {
			result += diagonal[i] * solutionVector[(sizeOfSystem - 1) - i];
			if (i != 0) {
				result += lowerDiagonal[i - 1] * static_cast<double>(solutionVector[(sizeOfSystem - 1) - i + 1]);
			}
			if (i != sizeOfSystem - 1) {
				result += upperDiagonal[i] * static_cast<double>(solutionVector[(sizeOfSystem - 1) - i - 1]);
			}
		}
		else if (i == posOfFirstRow)
		{
			for (int j = 0; j < sizeOfSystem; j++) {
				result += static_cast<double>(solutionVector[j]) * firstRow[j];
			}
		}
		else {
			for (int j = 0; j < sizeOfSystem; j++) {
				result += static_cast<double>(solutionVector[j]) * secondRow[j];
			}
		}

		freeColumn.push_back(result);
		result = 0;
	}
	return solutionVector;
}
std::vector<double> SystemOfLinearEquations::solve() {
	double R;

	//Step 1 
	for (int i = 0; i < posOfFirstRow; i++) {
		R = 1 / diagonal[i];
		diagonal[i] = 1;
		upperDiagonal[i] *= R;
		freeColumn[i] *= R;

		if (i != posOfFirstRow - 1) {
			R = lowerDiagonal[i];
			lowerDiagonal[i] = 0;
			diagonal[i + 1] -= R * upperDiagonal[i];
			freeColumn[i + 1] -= R * freeColumn[i];
		}
		R = firstRow[sizeOfSystem - i - 1];
		firstRow[sizeOfSystem - i - 1] = 0;
		freeColumn[posOfFirstRow] -= freeColumn[i] * R;
		firstRow[sizeOfSystem - i - 2] -= upperDiagonal[i] * R;

		R = secondRow[sizeOfSystem - i - 1];
		secondRow[sizeOfSystem - i - 1] = 0;
		freeColumn[posOfFirstRow + 1] -= freeColumn[i] * R;
		secondRow[sizeOfSystem - i - 2] -= upperDiagonal[i] * R;

	}

	/*outputToConsole();*/

	//Step 2
	for (int i = sizeOfSystem - 1; i > posOfFirstRow + 1; i--) {
		R = 1 / diagonal[i];
		diagonal[i] = 1;
		lowerDiagonal[i - 1] *= R;
		freeColumn[i] *= R;

		if (i != posOfFirstRow + 2) {
			R = upperDiagonal[i - 1];
			upperDiagonal[i - 1] = 0;
			diagonal[i - 1] -= R * lowerDiagonal[i - 1];
			freeColumn[i - 1] -= R * freeColumn[i];
		}
		R = firstRow[sizeOfSystem - i - 1];
		firstRow[sizeOfSystem - i - 1] = 0;
		freeColumn[posOfFirstRow] -= freeColumn[i] * R;
		firstRow[sizeOfSystem - i] -= lowerDiagonal[i - 1] * R;

		R = secondRow[sizeOfSystem - i - 1];
		secondRow[sizeOfSystem - i - 1] = 0;
		freeColumn[posOfFirstRow + 1] -= freeColumn[i] * R;
		secondRow[sizeOfSystem - i] -= lowerDiagonal[i - 1] * R;


	}

	/*outputToConsole();*/

	//Step 3.1
	R = 1 / secondRow[sizeOfSystem - posOfFirstRow - 2];
	secondRow[sizeOfSystem - posOfFirstRow - 2] = 1;
	secondRow[sizeOfSystem - posOfFirstRow - 1] *= R;
	freeColumn[posOfFirstRow + 1] *= R;

	

	//Step 3.2
	R = firstRow[sizeOfSystem - posOfFirstRow - 2];
	firstRow[sizeOfSystem - posOfFirstRow - 2] = 0;
	firstRow[sizeOfSystem - posOfFirstRow - 1] -= R * secondRow[sizeOfSystem - posOfFirstRow - 1];
	freeColumn[posOfFirstRow] -= R * freeColumn[posOfFirstRow + 1];


	//Step 3.3
	freeColumn[posOfFirstRow] /= firstRow[sizeOfSystem - posOfFirstRow - 1];
	firstRow[sizeOfSystem - posOfFirstRow - 1] = 1;

	/*outputToConsole();*/

	//Fix overlaps
	upperDiagonal[posOfFirstRow] = 0;
	diagonal[posOfFirstRow] = 1;
	diagonal[posOfFirstRow + 1] = 1;
	lowerDiagonal[posOfFirstRow] = secondRow[sizeOfSystem - posOfFirstRow - 1];

	outputToConsole();

	//Initialize solution vector

	std::vector<double> solution(sizeOfSystem);

	////Step 4
	//solution[posOfFirstRow] = freeColumn[posOfFirstRow];

	//for (int i = posOfFirstRow - 1; i >= 0; i--) {
	//	solution[i] = freeColumn[i] - upperDiagonal[i] * solution[i + 1];
	//}
	//for (int i = posOfFirstRow + 1; i < sizeOfSystem; i++) {
	//	solution[i] = freeColumn[i] - lowerDiagonal[i - 1] * solution[i - 1];
	//}
	//std::reverse(solution.begin(), solution.end());

	//Step 4(another option)
	int solIndex = sizeOfSystem - posOfFirstRow - 1;

	solution[solIndex] = freeColumn[posOfFirstRow];

	for (int i = posOfFirstRow - 1, j = solIndex + 1; i >= 0; i--, j++) {
		solution[j] = freeColumn[i] - upperDiagonal[i] * solution[j - 1];
	}

	for (int i = posOfFirstRow + 1, j = solIndex - 1; i < sizeOfSystem; i++, j--) {
		solution[j] = freeColumn[i] - lowerDiagonal[i - 1] * solution[j + 1];
	}

	return solution;
}



