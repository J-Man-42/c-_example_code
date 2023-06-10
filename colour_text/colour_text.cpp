#include <cctype>
#include "colour_text.h"
using namespace std;


// Returns the text provided in the given colour.
// If no colour is provided, return text as is.
string colourText(string text, char colour) {

	// Switch statement for each colour.
	switch (toupper(colour)) {
	case 'X':
		return "\033[1;30m" + text + "\033[0m";
	case 'R':
		return "\033[0;31m" + text + "\033[0m";
	case 'G':
		return "\033[0;32m" + text + "\033[0m";
	case 'Y':
		return "\033[0;33m" + text + "\033[0m";
	case 'B':
		return "\033[0;34m" + text + "\033[0m";
	case 'M':
		return "\033[0;35m" + text + "\033[0m";
	case 'C':
		return "\033[0;36m" + text + "\033[0m";
	case 'W':
		return "\033[0;37m" + text + "\033[0m";
	default:
		return text;
	}
}