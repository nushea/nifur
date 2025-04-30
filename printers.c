#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "printers.h"

int isTrueColor = 0;

int colmap(int color){ //{{{
	if(isTrueColor){
		switch(color){
			case -1: return 0x1e1e2e;
			case -2: return 0xcdd6f4;
			default: return 0xffffff;
		}
	}else{
		switch(color){
			case -1: return 40;
			case -2: return 97;
			default: return 107;
		}
	}
	return 0;
} //}}}

void ansi(int posX, int posY, int bg, int fg, char * output){ //{{{
	if(isTrueColor)
		truc(posX, posY, bg, fg, output);
	else
	 	dots(posX, posY, bg, fg, output);
} //}}}

void truc(int posX, int posY, int bg, int fg, char * output){ //{{{
	if(strlen(output)>=BUFFER){
		printf("\x1b[1;1H\x1b[107;40mOverflowing\n");
		return;
	}
		if(bg > 0xFFFFFF)
			bg=0xFFFFFF;
		if(fg > 0xFFFFFF)
			fg=0xFFFFFF;
		if(bg < 0)
			bg = colmap(bg);
		if(fg < 0){
			fg = colmap(bg);
		}
		char * oup;
		oup = malloc(BUFFER);
		memset(oup, 0, BUFFER);
		if(bg > -1)
			sprintf(oup, "\x1b[%i;%iH\x1b[38;2;%i;%i;%i;48;2;%i;%i;%im%s\x1b[0m\n", posY, posX, fg/0x10000, (fg/0x100)%0x100, fg%0x100, bg/0x10000, (bg/0x100)%0x100, bg%0x100, output);
		printf("%s", oup);
		free(oup);
	
} //}}}

void dots(int posX, int posY, int bg, int fg, char * output){ //{{{
	if(strlen(output)>=BUFFER){
		printf("\x1b[1;1H\x1b[107;40mOverflowing\n");
		return;
	}
	if(bg < 0)
		bg = colmap(bg);
	if(fg < 0)
		fg = colmap(bg);
	char * oup;
	oup = malloc(BUFFER);
    memset(oup, 0, BUFFER);
	sprintf(oup, "\x1b[%i;%iH\x1b[%i;%im%s\x1b[0m\n", posY, posX, fg, bg, output);
	printf("%s", oup);
	free(oup);
		
} //}}}

