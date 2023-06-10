#include <iostream>
#include "colour_text.h"
using namespace std;


int main() {
	cout << colourText("X --> grey", 'x') << endl;
	cout << colourText("R --> red", 'r') << endl;
	cout << colourText("G --> green", 'g') << endl;
	cout << colourText("Y --> yellow", 'y') << endl;
	cout << colourText("B --> blue", 'b') << endl;
	cout << colourText("M --> magenta", 'm') << endl;
	cout << colourText("C --> cyan", 'c') << endl;
	cout << colourText("W --> white", 'w') << endl;
	return 0;
}