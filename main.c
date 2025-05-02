#include "printers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char uri[BUFFER], host[BUFFER], ip[BUFFER], * modifiedURI, * modifiedURIp;
int ranPage = 0;

//{{{ Initialization process

void initProc(){ //{{{ The default displaying present on every page
	printf("\x1b[2J");

	char * spaces;
	spaces = malloc(81);
	memset(spaces, ' ', 80);
	spaces[80] = '\0';
	for(int i=1; i<=HEIGH; i++)
		ansi(1, i, colBG, colFG, spaces);
	free(spaces);

	int space = 8;
	ansi(1,1, colBG, -10, "$");
	ansi(3,1, colBG, -11, "curl");
	
	ansi(space,1, colBG, -12, host);
	space += strlen(host);
	strncpy(modifiedURI, getenv("REQUEST_URI"), BUFFER); 
	modifiedURI[BUFFER-1] = '\0';
	modifiedURI = strtok(modifiedURI, "/");
	char temp[BUFFER];
	while(modifiedURI != NULL){
		if((strncmp(modifiedURI, "nifur", 6))){
			sprintf(temp, "/%s", modifiedURI);
			ansi(space, 1, colBG, -13, temp);
			space += strlen(modifiedURI)+1;
		}
		modifiedURI = strtok(NULL, "/");
	}
	modifiedURI = modifiedURIp;
//	ansi(space,1, colBG, -13, uri);
//	space += strlen(uri);

	if(space < WIDTH-49)
		ansi((WIDTH-space-20)/2 + space - 14,1,colBG, colFG, "World's most boring trannie!");
	
	ansi(WIDTH-20,1,colBG, colFG, "(minimum size: 80x24)");
	printf("\x1b[%i;%iH\x1b[0\n", HEIGH, WIDTH+1);
}//}}}

//}}}

//{{{ Objects that can be drawn
void TallIndexCard(int posX, int posY, int sizX, int sizY, int bg, int earBG, int fg){ //{{{
	if(sizX < 20 || sizY < 6 || sizX+posX > 81 || sizY+posY > 25){
		ansi(posX, posY, colBG, colFG, "indexCard sizes X:20-80 Y:7-24");
		return;}

	if(isTrueColor){ //{{{
		ansi(posX+ 4,posY+ 0, earBG,   fg,     "▗▄▄▄▄▖");
		ansi(posX+ 2,posY+ 1, earBG,   fg,   "▄▛▀    ▜▖");
		ansi(posX   ,posY+ 2, earBG,   fg, "▗▛▘       ▌");
		ansi(posX   ,posY+ 3, earBG,   fg, "▟         ▙");
		ansi(posX+ 3,posY+ 1,    bg,   fg,    "▛▀    ▜");
		ansi(posX+ 1,posY+ 2,    bg,   fg,  "▛▘       ");
		ansi(posX+ 1,posY+ 3,    bg,   fg,  "         ");

		ansi(posX+sizX- 9,posY + 0, earBG, fg, "▗▄▄▄▄▖");
		ansi(posX+sizX-10,posY + 1, earBG, fg,"▗▛    ▀▜▄");
		ansi(posX+sizX-10,posY + 2, earBG, fg,"▐       ▝▜▖");
		ansi(posX+sizX-10,posY + 3, earBG, fg,"▟         ▙");
		ansi(posX+sizX- 9,posY + 1,    bg, fg, "▛    ▀▜");
		ansi(posX+sizX- 9,posY + 2,    bg, fg, "       ▝▜");
		ansi(posX+sizX- 9,posY + 3,    bg, fg, "         ");

		int overSize = 20;
		char over[BUFFER];
		memset(over, 0, BUFFER);
		strcpy(over, "▄");
		while(overSize < sizX-2){
			strcat(over, "▄");
			overSize+=1;
		}
		ansi(posX+11,posY+ 3, earBG,   fg, over);

		int ofy = 4;
		char background[80];
		memset(background, ' ', sizX-1);
		background[sizX-1] = '\0';
		while(ofy < sizY-1){	
			ansi(posX+1, posY+ofy, bg,   fg, background);
			ofy+=1;
		}
		ofy = 4;
		while(ofy < sizY-3){
			ansi(posX, posY+ ofy, bg,   fg, "▌");
			ansi(posX+sizX, posY+ ofy, bg,   fg, "▐");
			ofy += 1;
		}
		ansi(posX, posY+ ofy, colBG,   fg, "▜");
		ansi(posX+sizX, posY+ ofy, colBG,   fg, "▛");
		ansi(posX, posY+ ofy+1, colBG,   fg, "▝▙");
		ansi(posX+sizX-1, posY+ ofy+1, colBG,   fg, "▟▘");
		ansi(posX+1, posY+ ofy+2, colBG,   fg, "▝");
		ansi(posX+sizX-1, posY+ ofy+2, colBG,   fg, "▘");

		int underSize = 1;
		char under[BUFFER];
		memset(under, 0, BUFFER);
		strcpy(under, "▀");
		while(underSize < sizX-3){
			strcat(under, "▀");
			underSize+=1;
		}
		ansi(posX+2,posY + sizY-1, colBG,   fg, under);
	}//}}}
	else{ //{{{ simple color
		ansi(posX+ 4,posY+ 0, colBG,   fg,     "┌───┐");
		ansi(posX+ 1,posY+ 1, colBG,   fg,  "┌──┘   └┐");
		ansi(posX   ,posY+ 2, colBG,   fg, "┌┘   ──┐ └");
		ansi(posX   ,posY+ 3, colBG,   fg, "│");
		ansi(posX+ 5,posY+ 1,    bg,   fg,  "   ");
		ansi(posX+ 2,posY+ 2,    bg,   fg, "   ──┐ ");

		int overSize = 20;
		char over[BUFFER];
		memset(over, 0, BUFFER);
		strcpy(over, "─");
		while(overSize < sizX){
			strcat(over, "─");
			overSize+=1;
		}
		ansi(posX+overSize- 9,posY + 0,colBG, fg," ┌───┐");
		ansi(posX+overSize- 9,posY + 1,colBG, fg,"┌┘   └──┐");
		ansi(posX+overSize- 9,posY + 2,colBG, fg,"┘ ┌──   └┐");
		ansi(posX+overSize   ,posY + 3,colBG, fg,         "│");
		ansi(posX+overSize- 7,posY + 1,   bg, fg,"   ");
		ansi(posX+overSize- 8,posY + 2,   bg, fg," ┌──   ");

		ansi(posX+10,posY+ 2, colBG,   fg, over);

		int ofy = 4;
		while(ofy < sizY-2){
			ansi(posX, posY+ ofy, colBG,   fg, "│");
			ansi(posX+overSize, posY+ ofy, colBG,   fg, "│");
			ofy += 1;
		}
		ansi(posX, posY+ ofy, colBG,   fg, "└┐");
		ansi(posX+overSize-1, posY+ ofy, colBG,   fg, "┌┘");
		ansi(posX+1, posY+ ofy+1, colBG,   fg, "└");
		ansi(posX+overSize-1, posY+ ofy+1, colBG,   fg, "┘");

		int ows = 3;
		char background[80];
		memset(background, ' ', sizX-4);
		background[sizX-4] = 0;
		ansi(posX+3, posY+sizY-2, bg,   fg, background);
		background[sizX-2] = 0;
		memset(background, ' ', sizX-1);
		background[sizX-1] = 0;
		while(ows < sizY-2){	
			ansi(posX+1, posY+ows, bg,   fg, background);
			ows+=1;
		}
		int underSize = 2;
		char under[BUFFER];
		memset(under, 0, BUFFER);
		strcpy(under, "─");
		while(underSize < sizX-2){
			strcat(under, "─");
			underSize+=1;
		}
		ansi(posX+2,posY + sizY-1, colBG,   fg, under);

	} //}}}
} //}}}

void indexCard(int posX, int posY, int sizX, int sizY, int bg, int earBG, int fg){ //{{{
	if(sizX < 20 || sizY < 6 || sizX+posX > 81 || sizY+posY > 25){
		ansi(posX, posY, colBG, colFG, "indexCard sizes X:20-80 Y:7-24");
		return;}

	if(isTrueColor){ //{{{
		ansi(posX+ 5,posY+ 0, earBG,   fg,      "▄▄▄▄");
		ansi(posX+ 2,posY+ 1, earBG,   fg,   "▄▟▀▀  ▝▌");
		ansi(posX+ 4,posY+ 1,    bg,   fg,     "▀▀  ▝");
		ansi(posX   ,posY+ 2, earBG,   fg, "▗▛▘  ──┐ ▙");
		ansi(posX+ 1,posY+ 2,    bg,   fg,  "▛▘  ──┐ ");
		ansi(posX   ,posY+ 3, earBG,   fg, "▟");

		ansi(posX+sizX- 8,posY + 0, earBG, fg, "▄▄▄▄");
		ansi(posX+sizX- 9,posY + 1, earBG, fg,"▐▘  ▀▀▙▄");
		ansi(posX+sizX- 8,posY + 1,    bg, fg, "▘  ▀▀");
		ansi(posX+sizX- 9,posY + 2, earBG, fg,"▟ ┌──  ▝▜▖");
		ansi(posX+sizX- 8,posY + 2,    bg, fg," ┌──  ▝▜");
		ansi(posX+sizX   ,posY + 3, earBG, fg,        "▙");

		int overSize = 20;
		char over[BUFFER];
		memset(over, 0, BUFFER);
		strcpy(over, "▄");
		while(overSize < sizX){
			strcat(over, "▄");
			overSize+=1;
		}
		ansi(posX+10,posY+ 2, earBG,   fg, over);

		int ofy = 3;
		char background[80];
		memset(background, ' ', sizX-1);
		background[sizX-1] = '\0';
		while(ofy < sizY-1){	
			ansi(posX+1, posY+ofy, bg,   fg, background);
			ofy+=1;
		}
		ofy = 4;
		while(ofy < sizY-2){
			ansi(posX, posY+ ofy, bg,   fg, "▌");
			ansi(posX+overSize, posY+ ofy, bg,   fg, "▐");
			ofy += 1;
		}
		ansi(posX, posY+ ofy, bg,   fg, "▙");
		ansi(posX+overSize, posY+ ofy, bg,   fg, "▟");
		ansi(posX, posY+ ofy+1, colBG,   fg, "▝");
		ansi(posX+overSize, posY+ ofy+1, colBG,   fg, "▘");

		int underSize = 1;
		char under[BUFFER];
		memset(under, 0, BUFFER);
		strcpy(under, "▀");
		while(underSize < sizX-1){
			strcat(under, "▀");
			underSize+=1;
		}
		ansi(posX+1,posY + sizY-1, colBG,   fg, under);
	}//}}}
	else{ //{{{ simple color
		ansi(posX+ 4,posY+ 0, colBG,   fg,     "┌───┐");
		ansi(posX+ 1,posY+ 1, colBG,   fg,  "┌──┘   └┐");
		ansi(posX   ,posY+ 2, colBG,   fg, "┌┘   ──┐ └");
		ansi(posX   ,posY+ 3, colBG,   fg, "│");
		ansi(posX+ 5,posY+ 1,    bg,   fg,  "   ");
		ansi(posX+ 2,posY+ 2,    bg,   fg, "   ──┐ ");

		int overSize = 20;
		char over[BUFFER];
		memset(over, 0, BUFFER);
		strcpy(over, "─");
		while(overSize < sizX){
			strcat(over, "─");
			overSize+=1;
		}
		ansi(posX+overSize- 9,posY + 0,colBG, fg," ┌───┐");
		ansi(posX+overSize- 9,posY + 1,colBG, fg,"┌┘   └──┐");
		ansi(posX+overSize- 9,posY + 2,colBG, fg,"┘ ┌──   └┐");
		ansi(posX+overSize   ,posY + 3,colBG, fg,         "│");
		ansi(posX+overSize- 7,posY + 1,   bg, fg,"   ");
		ansi(posX+overSize- 8,posY + 2,   bg, fg," ┌──   ");

		ansi(posX+10,posY+ 2, colBG,   fg, over);

		int ofy = 4;
		while(ofy < sizY-2){
			ansi(posX, posY+ ofy, colBG,   fg, "│");
			ansi(posX+overSize, posY+ ofy, colBG,   fg, "│");
			ofy += 1;
		}
		ansi(posX, posY+ ofy, colBG,   fg, "└┐");
		ansi(posX+overSize-1, posY+ ofy, colBG,   fg, "┌┘");
		ansi(posX+1, posY+ ofy+1, colBG,   fg, "└");
		ansi(posX+overSize-1, posY+ ofy+1, colBG,   fg, "┘");

		int ows = 3;
		char background[80];
		memset(background, ' ', sizX-4);
		background[sizX-4] = 0;
		ansi(posX+3, posY+sizY-2, bg,   fg, background);
		background[sizX-2] = 0;
		memset(background, ' ', sizX-1);
		background[sizX-1] = 0;
		while(ows < sizY-2){	
			ansi(posX+1, posY+ows, bg,   fg, background);
			ows+=1;
		}
		int underSize = 2;
		char under[BUFFER];
		memset(under, 0, BUFFER);
		strcpy(under, "─");
		while(underSize < sizX-2){
			strcat(under, "─");
			underSize+=1;
		}
		ansi(posX+2,posY + sizY-1, colBG,   fg, under);

	} //}}}
} //}}}

void activeBox(int posX, int posY, int sizX, int sizY, int bg, int fg){//{{{
//	ansi(posX, posY, bg, fg, "active");
	if(sizX < 18 || sizY < 8 || sizX+posX > 81 || sizY+posY > 24){
		ansi(posX, posY, colBG, colFG, "activeBox sizes X:20-80 Y:7-24");
		return;}
	if(isTrueColor){ //{{{
		ansi(posX+5,posY   , colBG, fg,      "▄▄▄▄");
		ansi(posX+3,posY+ 1,    bg, fg,    "▀▀▀");
		ansi(posX+1,posY+ 1, colBG, fg,  "▄▟");
		ansi(posX+1,posY+ 2,    bg, fg,  "█");
		ansi(posX  ,posY+ 3,    bg, fg, "█▀");
		if(sizX > 18){	
			int overSize = 18;
			char over[BUFFER],under[BUFFER];
			memset(over, 0, BUFFER);
			memset(under, 0, BUFFER);
			strcpy(over, "▀");
			strcpy(under, "▄");
			while(overSize < sizX){
				strcat(over, "▀");
				strcat(under, "▄");
				overSize+=1;
			}
			ansi(posX+ 9,posY, bg,   fg, over);
			ansi(posX+ 9,posY+sizY-1, bg,   fg, under);
		}
		char background[80];
		memset(background,' ',sizX-12);
		background[sizX-12] = 0;
		ansi(posX+6,posY+ 1, bg, fg, background);
		ansi(posX+6,posY+sizY-2, bg, fg, background);
		memset(background,' ',sizX-4);
		background[sizX-4] = 0;
		ansi(posX+2,posY+ 2, bg, fg, background);
		ansi(posX+2,posY+sizY-3, bg, fg, background);
		ansi(posX+2,posY+ 3, bg, fg, background);
		ansi(posX+2,posY+sizY-4, bg, fg, background);
		memset(background,' ',sizX-2);
		background[sizX-2] = 0;
		int ofy = 4;
		while(ofy < sizY-4){
			ansi(posX, posY+ ofy, bg,   colFG, "▌");
			ansi(posX+sizX-1, posY+ ofy, bg,   colFG, "▐");
			ansi(posX+1,posY+ ofy, bg, fg, background);
			ofy += 1;
		}
		ansi(posX+sizX- 9,posY   , colBG, fg,   "▄▄▄▄");
		ansi(posX+sizX- 6,posY+ 1,    bg, fg,      "▀▀▀");
		ansi(posX+sizX- 3,posY+ 1, colBG, fg,         "▙▄");
		ansi(posX+sizX- 2,posY+ 2,    bg, fg,          "█");
		ansi(posX+sizX- 2,posY+ 3,    bg, fg,          "▀█");

		ansi(posX   , posY+sizY- 4,   bg, fg, "█▄");
		ansi(posX+ 1, posY+sizY- 3,   bg, fg,  "█");
		ansi(posX+ 1, posY+sizY- 2,colBG, fg,  "▀");
		ansi(posX+ 2, posY+sizY- 2,   bg, fg,   "▙▄▄▄");
		ansi(posX+ 5, posY+sizY- 1,colBG, fg,      "▀▀▀▀");
		
		ansi(posX+sizX- 2,posY+sizY- 4,    bg, fg,        "▄█");
		ansi(posX+sizX- 2,posY+sizY- 3,    bg, fg,        "█");
	   	ansi(posX+sizX- 3,posY+sizY- 2, colBG, fg,       "▛▀");
		ansi(posX+sizX- 6,posY+sizY- 2,    bg, fg,    "▄▄▄");
		ansi(posX+sizX- 9,posY+sizY- 1, colBG, fg, "▀▀▀▀");

	}//}}}
	else{ //{{{
			int overSize = 2;
			char over[BUFFER];
			memset(over, 0, BUFFER);
			strcpy(over, "─");
			while(overSize < sizX){
				strcat(over, "─");
				overSize+=1;
			}
			ansi(posX+ 1,posY, colBG,   fg, over);
			ansi(posX+ 1,posY+sizY-1, colBG,   fg, over);
		char background[80];
		memset(background,' ',sizX-12);
		background[sizX-12] = 0;
		ansi(posX+6,posY+ 1, bg, fg, background);
		ansi(posX+6,posY+sizY-2, bg, fg, background);
		memset(background,' ',sizX-4);
		background[sizX-4] = 0;
		ansi(posX+2,posY+ 2, bg, fg, background);
		ansi(posX+2,posY+sizY-3, bg, fg, background);
		ansi(posX+2,posY+ 3, bg, fg, background);
		ansi(posX+2,posY+sizY-4, bg, fg, background);
		memset(background,' ',sizX-2);
		background[sizX-2] = 0;
		int ofy = 1;
		while(ofy < sizY-1){
			ansi(posX, posY+ ofy, colBG,   colFG, "│");
			ansi(posX+sizX-1, posY+ ofy, colBG,   colFG, "│");
			ansi(posX+1,posY+ ofy, bg, fg, background);
			ofy += 1;
		}	
		ansi(posX,posY, colBG, fg, "┌");
		ansi(posX+sizX-1,posY, colBG, fg, "┐");
		ansi(posX,posY+sizY- 1, colBG, fg, "└");
		ansi(posX+sizX-1,posY+sizY- 1, colBG, fg, "┘");

	}//}}}


}//}}}

void shoru(int posX, int posY, int bg,int fg){//{{{
	if(posX > 50 || posY > 8){
		ansi(posX, posY, colBG,colFG,"OOBing it :c");
		return;
	}
	if(isTrueColor){ //{{{	
		ansi(posX+15, posY    ,  bg, fg,                "█");
		ansi(posX+14, posY + 1,  bg, fg,               "▄▀▄");
		ansi(posX+14, posY + 2, -41, fg,               "█ █");
		ansi(posX+13, posY + 3, -41, fg,              "█   █");
		ansi(posX+ 6, posY + 4,  bg, fg,       "▝▀█▜▄▄▄▀   ▀▄▄▄▛█▀▘");
		ansi(posX+ 8, posY + 5,  bg, fg,         "▀▄   ▀▀▄▀▀   ▄▀");
		ansi(posX+ 6, posY + 6,  bg, fg,       "▗▄▄█     █     █▄▄▖");
		ansi(posX   , posY + 7,  bg, fg, "▗▄▄▛▀▀▘   ▀▄▄▄▄█▄▄▄▄▀   ▝▀▀▜▄▄▖");
		ansi(posX   , posY + 8,  bg, fg, "▝▀▀▙▄▄▖   ▄▀▀▀▀█▀▀▀▀▄   ▗▄▄▟▀▀▘");
		ansi(posX+ 6, posY + 9,  bg, fg,       "▝▀▀█     █     █▀▀▘");
		ansi(posX+ 8, posY +10,  bg, fg,         "▄▀   ▄▄▀▄▄   ▀▄");
		ansi(posX+ 6, posY +11,  bg, fg,       "▗▄█▟▀▀▀▄   ▄▀▀▀▙█▄▖");
		ansi(posX+13, posY +12, -44, fg,              "█   █");
		ansi(posX+14, posY +13, -44, fg,               "█ █");
		ansi(posX+14, posY +14,  bg, fg,               "▀▄▀");
		ansi(posX+15, posY +15,  bg, fg,                "█");

		ansi(posX+15, posY + 1, -41, fg, "▀");
		ansi(posX+13, posY + 4, -41, fg, "▀   ▀");
		ansi(posX+15, posY + 5, -41, fg, "▄");
		ansi(posX+15, posY +10, -44, fg, "▀");
		ansi(posX+13, posY +11, -44, fg, "▄   ▄");
		ansi(posX+15, posY +14, -44, fg, "▄");
		ansi(posX+ 3, posY + 7, -42, fg, "▛▀▀▘   ▀");
		ansi(posX+ 3, posY + 8, -42, fg, "▙▄▄▖   ▄");
		ansi(posX+20, posY + 7, -43, fg, "▀   ▝▀▀▜");
		ansi(posX+20, posY + 8, -43, fg, "▄   ▗▄▄▟");
		ansi(posX+ 9, posY + 4,-103, fg, "▜");
		ansi(posX+ 9, posY + 5,-103, fg, "▄   ▀▀");
		ansi(posX+ 9, posY + 6,-103, fg, "█     ");
		ansi(posX+11, posY + 7,-103, fg, "▄▄▄▄");
		ansi(posX+21, posY + 4,-104, fg, "▛");
		ansi(posX+16, posY + 5,-104, fg, "▀▀   ▄");
		ansi(posX+16, posY + 6,-104, fg, "     █");
		ansi(posX+16, posY + 7,-104, fg, "▄▄▄▄");
		ansi(posX+11, posY + 8,-101, fg, "▀▀▀▀");
		ansi(posX+ 9, posY + 9,-101, fg, "█     ");
		ansi(posX+ 9, posY +10,-101, fg, "▀   ▄▄");
		ansi(posX+ 9, posY +11,-101, fg, "▟");
		ansi(posX+16, posY + 8,-102, fg, "▀▀▀▀");
		ansi(posX+16, posY + 9,-102, fg, "     ");
		ansi(posX+16, posY +10,-102, fg, "▄▄   ▀");
		ansi(posX+21, posY +11,-102, fg, "▙");
	} //}}}
	else{ //{{{ Basic colors

		ansi(posX+15,posY+ 0, bg, fg,                "█");
		ansi(posX+14,posY+ 1, bg, fg,               "▄▀▄");
		ansi(posX+14,posY+ 2,-41, fg,               "█ █");
		ansi(posX+13,posY+ 3,-41, fg,              "█   █");
		ansi(posX+ 7,posY+ 4, bg, fg,        "▀██▄▄▄▀   ▀▄▄▄██▀");
		ansi(posX+ 8,posY+ 5, bg, fg,         "▀▄   ▀▀▄▀▀   ▄▀");
		ansi(posX+ 7,posY+ 6, bg, fg,        "▄▄█     █     █▄▄");
		ansi(posX+ 1,posY+ 7, bg, fg,  "▄▄█▀▀▀   ▀▄▄▄▄█▄▄▄▄▀   ▀▀▀█▄▄");
		ansi(posX+ 1,posY+ 8, bg, fg,  "▀▀█▄▄▄   ▄▀▀▀▀█▀▀▀▀▄   ▄▄▄█▀▀");
		ansi(posX+ 7,posY+ 9, bg, fg,        "▀▀█     █     █▀▀");
		ansi(posX+ 8,posY+10, bg, fg,         "▄▀   ▄▄▀▄▄   ▀▄");
		ansi(posX+ 7,posY+11, bg, fg,        "▄██▀▀▀▄   ▄▀▀▀██▄");
		ansi(posX+13,posY+12,-44, fg,              "█   █");
		ansi(posX+14,posY+13,-44, fg,               "█ █");
		ansi(posX+14,posY+14, bg, fg,               "▀▄▀");
	    ansi(posX+15,posY+15, bg, fg,                "█");

		ansi(posX+15, posY + 1, -41, fg, "▀");
		ansi(posX+13, posY + 4, -41, fg, "▀   ▀");
		ansi(posX+15, posY + 5, -41, fg, "▄");
		ansi(posX+15, posY +10, -44, fg, "▀");
		ansi(posX+13, posY +11, -44, fg, "▄   ▄");
		ansi(posX+15, posY +14, -44, fg, "▄");
		ansi(posX+ 3, posY + 7, -42, fg, "█▀▀▀   ▀");
		ansi(posX+ 3, posY + 8, -42, fg, "█▄▄▄   ▄");
		ansi(posX+20, posY + 7, -43, fg, "▀   ▀▀▀█");
		ansi(posX+20, posY + 8, -43, fg, "▄   ▄▄▄█");
		ansi(posX+ 9, posY + 5,-103, fg, "▄   ▀▀");
		ansi(posX+ 9, posY + 6,-103, fg, "█     ");
		ansi(posX+11, posY + 7,-103, fg, "▄▄▄▄");
		ansi(posX+16, posY + 5,-106, fg, "▀▀   ▄");
		ansi(posX+16, posY + 6,-106, fg, "     █");
		ansi(posX+16, posY + 7,-106, fg, "▄▄▄▄");
		ansi(posX+11, posY + 8,-101, fg, "▀▀▀▀");
		ansi(posX+ 9, posY + 9,-101, fg, "█     ");
		ansi(posX+ 9, posY +10,-101, fg, "▀   ▄▄");
		ansi(posX+16, posY + 8,-102, fg, "▀▀▀▀");
		ansi(posX+16, posY + 9,-102, fg, "     ");
		ansi(posX+16, posY +10,-102, fg, "▄▄   ▀");
	} //}}}
}//}}}
//}}}

//{{{ Page Displays
void basicPage(){ //{{{
	activeBox(25, 3, 55, 15, -3, colFG);
	shoru(1, 3, colBG, -4);
	indexCard( 18, 15, 25, 10, -3, -3, colFG);
	TallIndexCard( 50, 12, 27, 13, -3, -3, colFG);
	
	ranPage = 1;
} //}}}

void debug(){//{{{	
	char debugstring[BUFFER*4];
	sprintf(debugstring, "Domain: %s%s\nYer ip is: %s", host,uri, ip);
	ansi(1, HEIGH-2, colBG, colFG, debugstring);
	ranPage = 1;
}//}}}
//}}}

int main(){ //{{{
	//{{{ Initializing the header reading
	modifiedURI = malloc(BUFFER);
	int tokenCount = 0;
    printf("Content-Type: text/plain\n\n");
	if(!(getenv("REQUEST_URI")&&getenv("SERVER_NAME")&&getenv("REMOTE_ADDR"))){
		printf("freaky ahh request\n");
		return -1;
	}
	
	strncpy(uri, getenv("REQUEST_URI"), BUFFER); uri[BUFFER-1] = '\0';
	strncpy(host, getenv("SERVER_NAME"), BUFFER); host[BUFFER-1] = '\0';
	strncpy(ip, getenv("REMOTE_ADDR"), BUFFER); ip[BUFFER-1] = '\0';
	isTrueColor = 1;
	
	//}}}

	//{{{ check for the simple-style flag
	strncpy(modifiedURI, getenv("REQUEST_URI"), BUFFER); modifiedURI[BUFFER-1] = '\0';
	modifiedURIp = modifiedURI;
	modifiedURI = strtok(modifiedURI, "/");

	while(modifiedURI != NULL){
		if(!(strncmp(modifiedURI, "simpl", 6))||!(strncmp(modifiedURI, "simple", 7))||!(strncmp(modifiedURI, "s", 2))){
			isTrueColor = 0;
			tokenCount = -1;
		}
		modifiedURI = strtok(NULL, "/");
	}
	modifiedURI = modifiedURIp;
	//}}}

	initProc();

	//{{{ check uri website
	
	strncpy(modifiedURI, getenv("REQUEST_URI"), BUFFER); 
	modifiedURI[BUFFER-1] = '\0';
	modifiedURI = strtok(modifiedURI, "/");
	while(modifiedURI != NULL){
		if(!(strncmp(modifiedURI, "debug", 6)))
			debug();
		if(!(strncmp(modifiedURI, "nifur", 6))){
			modifiedURI = strtok(NULL, "/");
			continue;
		}
		tokenCount += 1;
		modifiedURI = strtok(NULL, "/");
	}
	modifiedURI = modifiedURIp;
	if(!ranPage){
		if(tokenCount<=0){
			basicPage();
		}
		else{
			ansi(2, 2, colBG, colFG, "himitsu :3");
		}
	}

	//}}}
	ansi(1, HEIGH-1, colBG, colFG, "\n");
	free(modifiedURIp);
}//}}}

