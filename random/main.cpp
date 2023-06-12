#include <iostream>
#include "random.h"
using namespace std;


int main() {
	
	// Generate random values.
	cout << "randInt(-10, 9) = " << randInt(-10, 9) << endl;
	cout << "randUint(2, 19) = " << randInt(2, 19) << endl;
	cout << "randDouble(1.0, 2.0) = " << randDouble(1.0, 2.0) << endl;
	return 0;
}