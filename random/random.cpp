#include <cstdlib> // For rand() and srand()
#include <ctime>   // for time()
#include "random.h"


// The static seed value.
static uint long seed = 0;


// Update the random seed to epoch time.
void updateSeed() {
	if (seed == 0) {
		seed = time(0);
		srand(seed);
	}
}


// Generate a random signed integer between minValue and maxValue.
int randInt(int minValue, int maxValue) {
	updateSeed();
	return rand() % (maxValue - minValue + 1) + minValue;
}


// Generate a random unsigned integer between minValue and maxValue.
uint randUint(uint minValue, uint maxValue) {
	updateSeed();
	return rand() % (maxValue - minValue + 1) + minValue;
}


// Generate a random double between minValue and maxValue.
double randDouble(double minValue, double maxValue) {
	updateSeed();
	double randValue = double(rand()) / RAND_MAX;
    return randValue * (maxValue - minValue) + minValue;
}