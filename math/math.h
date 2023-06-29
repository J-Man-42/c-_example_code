#ifndef MIN_MAX_H
#define MIN_MAX_H

// A collection of math functions not included in <cmath>.

// All minimum in array prototypes.
uint min(uint arr[], const uint SIZE);
int min(int arr[], const uint SIZE);
double min(double arr[], const uint SIZE);
char min(char arr[], const uint SIZE);

// All minimum of two values prototypes.
uint min(uint a, uint b);
int min(int a, int b);
double min(double a, double b);
char min(char a, char b);

// All maximum in array prototypes.
uint max(uint arr[], const uint SIZE);
int max(int arr[], const uint SIZE);
double max(double arr[], const uint SIZE);
char max(char arr[], const uint SIZE);

// All maximum of two values prototypes.
uint max(uint a, uint b);
int max(int a, int b);
double max(double a, double b);
char max(char a, char b);

// Log base n of x.
double log(double n, double x);

#endif
