#include <iostream>
#include <sstream>
#include "colour_text.h"
using namespace std;


// Main testing function
int main() {

	// Configure the colours and titles.
	const size_t SIZE = 8;
	char colour[] = {'X', 'R', 'G', 'Y', 'B', 'M', 'C', 'W'};
	string title[] = {
		"grey",
		"red",
		"green",
		"yellow",
		"blue",
		"magenta",
		"cyan",
		"white"
	};

	// Loop through all titles.
	stringstream ss;
	string gamma;
	bool isBright;
	for (int i = 0; i < 2; i++) {
		gamma = (i == 0 ? "dark " : "bright ");
		isBright = i > 0;
		for (uint j = 0; j < SIZE; j++) {
			ss << colour[j] << " --> " << gamma << title[j];
			cout << colourText(ss.str(), colour[j], isBright) << endl;
			ss.str("");
		}
	}
	return 0;
}