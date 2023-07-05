#ifndef MOVE_CURSOR
#define MOVE_CURSOR

// Function prototypes.
void positionCursor(unsigned L, unsigned C);
void moveCursorUp(unsigned N);
void moveCursorDown(unsigned N);
void moveCursorRight(unsigned N);
void moveCursorLeft(unsigned N);
void clearScreen();
void eraseRight();
void saveCursorPosition();
void restoreCursorPosition();

#endif
