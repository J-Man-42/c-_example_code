#ifndef RANDOM_H
#define RANDOM_H

// All function prototypes.
void updateSeed();
int randInt(int minValue, int maxValue);
uint randUint(uint minValue, uint maxValue);
double randDouble(double minValue, double maxValue);
char randChar(char type = '\0');
int* randIntArray(const uint SIZE, int minValue, int maxValue);
uint* randUintArray(const uint SIZE, uint minValue, uint maxValue);
double* randDoubleArray(const uint SIZE, double minValue, double maxValue);
char* randCharArray(const uint SIZE, char type = '\0');
void shuffle(int* array, const uint SIZE);
void shuffle(uint* array, const uint SIZE);
void shuffle(double* array, const uint SIZE);
void shuffle(char* array, const uint SIZE);

#endif
