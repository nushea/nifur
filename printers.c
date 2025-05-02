#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "printers.h"

int isTrueColor = 0;

int colmap(int color){ //{{{
	if(isTrueColor){
		switch(color){
			case   -1: return 0x1e1e2e; // default background
			case   -2: return 0xcdd6f4; // default text color
			case   -3: return 0x313244; // secondary background
			case   -4: return 0x13131e; // mute over background
			case  -10: return 0xa6e3a1; // Pound sign for commands
			case  -11: return 0x89b4fa; // the literal "curl" text
			case  -12: return 0xfab387; // the domain
			case  -13: return 0xf38ba8; // the subdomain

			case  -30: case  -40: return 0x000000;
			case  -31: case  -41: return 0xFF0000;
			case  -32: case  -42: return 0x00FF00;
			case  -33: case  -43: return 0xFFFF00;
			case  -34: case  -44: return 0x0000FF;
			case  -35: case  -45: return 0xFF00FF;
			case  -36: case  -46: return 0x00FFFF;
			case  -37: case  -47: return 0xCCCCCC;
			case  -90: case -100: return 0x888888;
			case  -91: case -101: return 0xFF8888;
			case  -92: case -102: return 0x88FF88;
			case  -93: case -103: return 0xFFFF88;
			case  -94: case -104: return 0x8888FF;
			case  -95: case -105: return 0xFF88FF;
			case  -96: case -106: return 0x88FFFF;
			case  -97: case -107: return 0xFFFFFF;

			default:  return 0xffffff;
		}
	}else{
		color = -color;
		if((color >= 30 && color <= 37)||(color >= 40 && color <= 47)||(color >= 90 && color <= 97)||(color >= 100 && color <= 107))
			return color;
		color = -color;
		switch(color){
			case   -3:
			case   -1: return 40;
			case   -2: return 97;
			case   -4: return 90;
			case  -10: return 32; // Pound sign for commands
			case  -11: return 94; // the literal "curl" text
			case  -12: return 93; // the domain
			case  -13: return 95; // the subdomain

			default:  return 107;
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
			fg = colmap(fg);
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
		fg = colmap(fg);
	char * oup;
	oup = malloc(BUFFER);
    memset(oup, 0, BUFFER);
	sprintf(oup, "\x1b[%i;%iH\x1b[%i;%im%s\x1b[0m\n", posY, posX, fg, bg, output);
	printf("%s", oup);
	free(oup);
		
} //}}}

