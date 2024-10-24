#include "randint.h"

std::random_device rd;
std::mt19937 mt(rd());

int randint(int min, int max) {
	std::uniform_int_distribution<> dist(min, max); // Min and max inclusive

	return dist(mt);
}
