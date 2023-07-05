#ifndef RANDOM_H
#define RANDOM_H

// All function prototypes.
void updateSeed();
int randInt(int minValue, int maxValue);
unsigned randUint(unsigned minValue, unsigned maxValue);
double randDouble(double minValue, double maxValue);
char randChar(char type = '\0');
int* randIntArray(const unsigned SIZE, int minValue, int maxValue);
unsigned* randUintArray(const unsigned SIZE, unsigned minValue, unsigned maxValue);
double* randDoubleArray(const unsigned SIZE, double minValue, double maxValue);
char* randCharArray(const unsigned SIZE, char type = '\0');
void shuffle(int* array, const unsigned SIZE);
void shuffle(unsigned* array, const unsigned SIZE);
void shuffle(double* array, const unsigned SIZE);
void shuffle(char* array, const unsigned SIZE);

#endif
