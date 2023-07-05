#ifndef MIN_MAX_H
#define MIN_MAX_H

// A collection of math functions not included in <cmath>.

// All minimum in array prototypes.
unsigned min(unsigned arr[], const unsigned SIZE);
int min(int arr[], const unsigned SIZE);
double min(double arr[], const unsigned SIZE);
char min(char arr[], const unsigned SIZE);

// All minimum of two values prototypes.
unsigned min(unsigned a, unsigned b);
int min(int a, int b);
double min(double a, double b);
char min(char a, char b);

// All maximum in array prototypes.
unsigned max(unsigned arr[], const unsigned SIZE);
int max(int arr[], const unsigned SIZE);
double max(double arr[], const unsigned SIZE);
char max(char arr[], const unsigned SIZE);

// All maximum of two values prototypes.
unsigned max(unsigned a, unsigned b);
int max(int a, int b);
double max(double a, double b);
char max(char a, char b);

// Log base n of x.
double log(double n, double x);

#endif
