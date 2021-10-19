#pragma once
#include <random>
class Random
{
private:
	const int powerOfTen[6] = { 1, 10, 100, 1000, 10000, 100000};
	const int presicion;
	std::default_random_engine& global_urng();
public:
	Random();
	Random(const int&);
	void randomize();

	int randomInt(const int&);
	int randomInt(const int&, const int&);
	int randomIntOfOrderOfMagnitude(const int&);

	double randomDouble(const int&);
	double randomDouble(const double&, const double&);
	int randomDoubleOfOrderOfMagnitude(const int&);
};


