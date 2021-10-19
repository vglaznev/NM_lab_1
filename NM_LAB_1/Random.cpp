#include "Random.h"

Random::Random() : presicion(2) {}
Random::Random(const int& presicion) : presicion(presicion) {}

std::default_random_engine& Random::global_urng(){
	static std::default_random_engine u{};
	return u;
}
void Random::randomize() {
		static std::random_device rd{};
		global_urng().seed(rd());
}
int Random::randomInt(const int& e) {
	return randomInt(-1 * powerOfTen[e], powerOfTen[e]);
}

int Random::randomInt(const int& from, const int& upto) {
	static std::uniform_int_distribution<> d{};
	using parm_t = decltype(d)::param_type;
	return d(global_urng(), parm_t{ from, upto });
}

int Random::randomIntOfOrderOfMagnitude(const int& e) {
	return randomInt(powerOfTen[e], powerOfTen[e + 1] - 1);
}

double Random::randomDouble(const int& e) {
	return randomDouble(-1.0 * powerOfTen[e], powerOfTen[e]);
}

double Random::randomDouble(const double& from, const double& upto) {
	static std::uniform_real_distribution<> d{};
	using parm_t = decltype(d)::param_type;
	double truncated = std::trunc(d(global_urng(), parm_t{ from, upto }) * powerOfTen[presicion]) / powerOfTen[presicion];
	return truncated;
}

int Random::randomDoubleOfOrderOfMagnitude(const int& e) {
	return randomInt(powerOfTen[e], powerOfTen[e + 1] - 1);
}