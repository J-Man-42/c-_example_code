#include <iostream>
#include "move_cursor.h"
using namespace std;


// Move the cursor to the given line and column number.
void positionCursor(unsigned L, unsigned C) {
	cout << "\033["<<L<<";"<<C<<"H";
}


// Move the cursor up N lines.
void moveCursorUp(unsigned N) {
	cout << "\033["<<N<<"A";
}


// Move the cursor down N lines.
void moveCursorDown(unsigned N) {
	cout << "\033["<<N<<"B";
}


// Move the cursor forward N columns.
void moveCursorRight(unsigned N) {
	cout << "\033["<<N<<"C";
}


// Move the cursor backward N columns.
void moveCursorLeft(unsigned N) {
	cout << "\033["<<N<<"D";
}


// Clear the screen and move to position (0,0).
void clearScreen() {
	cout << "\033[2J\033[0;0H";
}


// Erase to end of line.
void eraseRight() {
	cout << "\033[K";
}


// Save cursor position.
void saveCursorPosition() {
	cout << "\033[s";
}


// Restore cursor position.
void restoreCursorPosition() {
	cout << "\033[u";
}
