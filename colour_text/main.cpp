#include <iostream>
#include <sstream>
#include "colour_text.h"
using namespace std;


// Main testing function
int main() {

	// Configure the colours and titles.
	const unsigned SIZE = 8;
	char colours[] = {'X', 'R', 'G', 'Y', 'B', 'M', 'C', 'W'};
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
	char colour;
	cout << "Colour texts:" << endl;
	for (unsigned i = 0; i < 2; i++) {
		gamma = (i == 0 ? "bright " : "dark ");
		for (unsigned j = 0; j < SIZE; j++) {
			colour = (i == 0 ? tolower(colours[j]) : colours[j]);
			ss << colour << " --> " << gamma << title[j];
			cout << colourText(ss.str(), colour) << endl;
			ss.str("");
		}
	}

	// Starting and ending specific colours.
	cout << "\nColour start and end:" << endl;
	for (unsigned i = 0; i < 2; i++) {
		gamma = (i == 0 ? "bright " : "dark ");
		for (unsigned j = 0; j < SIZE; j++) {
			colour = (i == 0 ? tolower(colours[j]) : colours[j]);
			startColour(colour);
			cout << colour;
			endColour();
			cout << " --> ";
			startColour(colour);
			cout << gamma << title[j] << endl;
			endColour();
		}
	}
	return 0;
}
