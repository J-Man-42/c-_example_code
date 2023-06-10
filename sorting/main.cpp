#include <iostream>
#include <cstdlib>
#include <ctime>
#include "sorting.h"
#include "../min_and_max/min_max.h"
using namespace std;


int main() {
	
	// Initialise array.
	const uint SIZE = 30;
	uint arr[SIZE];
	for (uint i = 0; i < SIZE; i++) {
		arr[i] = randint(1, 40);
		cout << arr[i] << " ";
	}
	cout << endl;

	cout << "\nDisplay array as bars:" << endl;
	displayArray(arr, SIZE);

	return 0;
}