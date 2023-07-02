#include <iostream>
#include "move_cursor.h"
using namespace std;


// Show the options menu.
void showMenu() {
	cout << "┌──────────────────────────────┐\n";
	cout << "│ (H)  Show this menu          │\n";
	cout << "│ (1)  positionCursor(L, C)    │\n";
	cout << "│ (2)  moveCursorUp(N)         │\n";
	cout << "│ (3)  moveCursorDown(N)       │\n";
	cout << "│ (4)  moveCursorRight(N)      │\n";
	cout << "│ (5)  moveCursorLeft(N)       │\n";
	cout << "│ (6)  clearScreen()           │\n";
	cout << "│ (7)  eraseRight()            │\n";
	cout << "│ (8)  saveCursorPosition()    │\n";
	cout << "│ (9)  restoreCursorPosition() │\n";
	cout << "│ (Q)  << QUIT PROGRAM >>      │\n";
	cout << "└──────────────────────────────┘\n";
}


// Main testing function.
int main() {
	char answer;
	uint L, C, N;

	// Show the initial menu.
	showMenu();

	// Loop until Q has been entered.
	while (answer != 'Q') {

		// Get user input
		cout << "> ";
		cin >> answer;
		answer = toupper(answer);


		// Switch statement for selection.
		switch (answer) {

		// Show the help menu.
		case 'H':
			showMenu();
			break;

		// Move the cursor position.
		case '1':
			cout << "> L = ";
			cin >> L;
			cout << "> C = ";
			cin >> C;
			positionCursor(L, C);
			break;

		// Move cursor up by N lines.
		case '2':
			cout << "> N = ";
			cin >> N;
			moveCursorUp(N);
			break;

		// Move cursor down by N lines.
		case '3':
			cout << "> N = ";
			cin >> N;
			moveCursorDown(N);
			break;

		// Move cursor right by N columns.
		case '4':
			cout << "> N = ";
			cin >> N;
			moveCursorRight(N);
			break;

		// Move cursor left by N columns.
		case '5':
			cout << "> N = ";
			cin >> N;
			moveCursorLeft(N);
			break;

		// Clear screen and reset position.
		case '6':
			clearScreen();
			break;

		// Erase to end of line.
		case '7':
			eraseRight();
			break;

		// Save cursor position.
		case '8':
			saveCursorPosition();
			break;

		// Restore cursor position.
		case '9':
			restoreCursorPosition();
			break;

		}
	}
	return 0;
}
