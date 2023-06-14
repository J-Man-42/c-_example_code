#include <cctype>
#include "colour_text.h"
using namespace std;


// Returns the text provided in the given colour.
// If no colour is provided, return text as is.
string colourText(string text, char colour, bool isBright) {
	string gamma = to_string(isBright);
	colour = toupper(colour);

	// Switch statement for each colour.
	switch (colour) {
	case 'X':
		return "\033["+gamma+";30m"+text+"\033[0m";
	case 'R':
		return "\033["+gamma+";31m"+text+"\033[0m";
	case 'G':
		return "\033["+gamma+";32m"+text+"\033[0m";
	case 'Y':
		return "\033["+gamma+";33m"+text+"\033[0m";
	case 'B':
		return "\033["+gamma+";34m"+text+"\033[0m";
	case 'M':
		return "\033["+gamma+";35m"+text+"\033[0m";
	case 'C':
		return "\033["+gamma+";36m"+text+"\033[0m";
	case 'W':
		return "\033["+gamma+";37m"+text+"\033[0m";
	default:
		return text;
	}
}