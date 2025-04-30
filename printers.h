#ifndef PRINTERSC
#define PRINTERSC


#define BUFFER 0x400
#define WIDTH 80
#define HEIGH 24

#define colBG -1
#define colFG -2

extern int isTrueColor;

int colmap(int color);

void ansi(int posX, int posY, int bg, int fg, char * output);

void truc(int posX, int posY, int bg, int fg, char * output);

void dots(int posX, int posY, int bg, int fg, char * output);


#endif
