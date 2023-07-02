#ifndef MOVE_CURSOR
#define MOVE_CURSOR

// Function prototypes.
void positionCursor(uint L, uint C);
void moveCursorUp(uint N);
void moveCursorDown(uint N);
void moveCursorRight(uint N);
void moveCursorLeft(uint N);
void clearScreen();
void eraseRight();
void saveCursorPosition();
void restoreCursorPosition();

#endif
