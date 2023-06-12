#include <iostream>
#include "move_cursor.h"
using namespace std;


// Move the cursor to the given line and column number.
void positionCursor(uint L, uint C) {
	cout << "\033["<<L<<";"<<C<<"H";
}


// Move the cursor up N lines.
void moveCursorUp(uint N) {
	cout << "\033["<<N<<"A";
}


// Move the cursor down N lines.
void moveCursorDown(uint N) {
	cout << "\033["<<N<<"B";
}


// Move the cursor forward N columns.
void moveCursorRight(uint N) {
	cout << "\033["<<N<<"C";
}


// Move the cursor backward N columns.
void moveCursorLeft(uint N) {
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