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
	//{{{ Draw URI
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
	//}}}

	if(space < WIDTH-43)
		ansi((WIDTH-space-20)/2 + space - 11,1,colBG, colFG, "Shea scented lavander!");
	
	ansi(WIDTH-20,1,colBG, colFG, "(minimum size: 80x24)");
	printf("\x1b[%i;%iH\x1b[0\n", HEIGH, WIDTH+1);
}//}}}

//}}}

//{{{ Objects that can be drawn
void SocialCard(int posX, int posY, int sizX, int sizY, int bg, int earBG, int fg){ //{{{
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
		ansi(posX+ 4,posY+ 0, colBG,   fg,     "┌────┐");
		ansi(posX+ 2,posY+ 1, colBG,   fg,   "┌─┘    └┐");
		ansi(posX   ,posY+ 2, colBG,   fg, "┌─┘  ──┐  │");
		ansi(posX   ,posY+ 3, colBG,   fg, "│         └");
		ansi(posX   ,posY+ 4, colBG,   fg, "│");
		ansi(posX+ 5,posY+ 2,    bg,   fg,  "   ");
		ansi(posX+ 4,posY+ 2,    bg,   fg, " ──┐ ");

		int overSize = 20;
		char over[BUFFER];
		memset(over, 0, BUFFER);
		strcpy(over, "─");
		while(overSize < sizX-2){
			strcat(over, "─");
			overSize+=1;
		}


		ansi(posX+overSize- 7,posY + 0,colBG, fg, "┌────┐");
		ansi(posX+overSize- 8,posY + 1,colBG, fg,"┌┘    └─┐");
		ansi(posX+overSize- 8,posY + 2,colBG, fg,"│ ┌──   └─┐");
		ansi(posX+overSize- 8,posY + 3,colBG, fg,"┘         │");
		ansi(posX+overSize   ,posY + 4,colBG, fg,         "│");
		ansi(posX+sizX- 7,posY + 1,   bg, fg,"   ");
		ansi(posX+sizX- 8,posY + 2,   bg, fg," ┌──  ");

		ansi(posX+11,posY+ 3, colBG,   fg, over);

		int ofy = 4;
		while(ofy < sizY-2){
			ansi(posX, posY+ ofy, colBG,   fg, "│");
			ansi(posX+sizX, posY+ ofy, colBG,   fg, "│");
			ofy += 1;
		}

		int ows = 4;
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
		ansi(posX, posY+ sizY- 3, colBG,   fg, "└┐");
		ansi(posX+sizX-1, posY+ sizY - 3, colBG,   fg, "┌┘");
		ansi(posX+1, posY+ sizY -2, colBG,   fg, "│");
		ansi(posX+sizX-1, posY+ sizY -2, colBG,   fg, "│");
		ansi(posX+1, posY+ sizY-1, colBG,   fg, "└");
		ansi(posX+sizX-1, posY+ sizY-1, colBG,   fg, "┘");
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

void indexCard(int posX, int posY, int sizX, int sizY, int bg, int LearBG, int RearBG, int fg){ //{{{
	if(sizX < 20 || sizY < 6 || sizX+posX > 81 || sizY+posY > 25){
		ansi(posX, posY, colBG, colFG, "indexCard sizes X:20-80 Y:7-24");
		return;}

	if(isTrueColor){ //{{{
		ansi(posX+ 5,posY+ 0, LearBG,   fg,      "▄▄▄▄");
		ansi(posX+ 2,posY+ 1, LearBG,   fg,   "▄▟▀▀  ▝▌");
		ansi(posX+ 4,posY+ 1,    bg,   fg,     "▀▀  ▝");
		ansi(posX   ,posY+ 2, LearBG,   fg, "▗▛▘  ──┐ ▙");
		ansi(posX+ 1,posY+ 2,    bg,   fg,  "▛▘  ──┐ ");
		ansi(posX   ,posY+ 3, LearBG,   fg, "▟");

		ansi(posX+sizX- 8,posY + 0, RearBG, fg, "▄▄▄▄");
		ansi(posX+sizX- 9,posY + 1, RearBG, fg,"▐▘  ▀▀▙▄");
		ansi(posX+sizX- 8,posY + 1,    bg, fg, "▘  ▀▀");
		ansi(posX+sizX- 9,posY + 2, RearBG, fg,"▟ ┌──  ▝▜▖");
		ansi(posX+sizX- 8,posY + 2,    bg, fg," ┌──  ▝▜");
		ansi(posX+sizX   ,posY + 3, RearBG, fg,        "▙");

		int overSize = 20;
		char over[BUFFER];
		memset(over, 0, BUFFER);
		strcpy(over, "▄");
		while(overSize < sizX){
			strcat(over, "▄");
			overSize+=1;
		}
		ansi(posX+10,posY+ 2, RearBG,   fg, over);

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
	if(sizX < 14 || sizY < 4 || sizX+posX > 81 || sizY+posY > 24){
		ansi(posX, posY, colBG, colFG, "activeBox sizes X:20-80 Y:7-24");
		return;}
	if(isTrueColor){ //{{{
		ansi(posX+5,posY   , colBG, fg,      "▄▄▄▄");
		ansi(posX+3,posY+ 1,    bg, fg,    "▀▀▀");
		ansi(posX+1,posY+ 1, colBG, fg,  "▄▟");
		ansi(posX+1,posY+ 2,    bg, fg,  "█");
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
			ansi(posX, posY+ ofy, bg,   fg, "█");
			ansi(posX+sizX-1, posY+ ofy, bg,   fg, "█");
			ansi(posX+1,posY+ ofy, bg, fg, background);
			ofy += 1;
		}
		ansi(posX+sizX- 9,posY   , colBG, fg,   "▄▄▄▄");
		ansi(posX+sizX- 6,posY+ 1,    bg, fg,      "▀▀▀");
		ansi(posX+sizX- 3,posY+ 1, colBG, fg,         "▙▄");
		ansi(posX+sizX- 2,posY+ 2,    bg, fg,          "█");
		if(sizY > 6){
			ansi(posX        ,posY+sizY- 4, bg, fg, "█▄");
			ansi(posX+sizX- 2,posY+sizY- 4, bg, fg, "▄█");
			ansi(posX        ,posY+ 3     , bg, fg, "█▀");
		ansi(posX+sizX- 2    ,posY+ 3     , bg, fg, "▀█");
		}
		else{
			ansi(posX+1        ,posY+sizY- 4, bg, fg, "█");
			ansi(posX+sizX- 2  ,posY+sizY- 4, bg, fg, "█");
			ansi(posX+1        ,posY+ 3     , bg, fg, "█");
			ansi(posX+sizX- 2  ,posY+ 3     , bg, fg, "█");
		}
		
		ansi(posX+ 1, posY+sizY- 3,   bg, fg,  "█");
		ansi(posX+ 1, posY+sizY- 2,colBG, fg,  "▀");
		ansi(posX+ 2, posY+sizY- 2,   bg, fg,   "▙▄▄▄");
		ansi(posX+ 5, posY+sizY- 1,colBG, fg,      "▀▀▀▀");
		
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
			ansi(posX, posY+ ofy, colBG,   fg, "│");
			ansi(posX+sizX-1, posY+ ofy, colBG,   fg, "│");
			ansi(posX+1,posY+ ofy, bg, fg, background);
			ofy += 1;
		}	
		ansi(posX,posY, colBG, fg, "┌");
		ansi(posX+sizX-1,posY, colBG, fg, "┐");
		ansi(posX,posY+sizY- 1, colBG, fg, "└");
		ansi(posX+sizX-1,posY+sizY- 1, colBG, fg, "┘");

	}//}}}


}//}}}

void shoru(int posX, int posY, int bg, int leftbg, int rightbg,int fg){//{{{
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
		ansi(posX   , posY + 7, leftbg, fg, "▗▄▄");
		ansi(posX   , posY + 8, leftbg, fg, "▝▀▀");
		ansi(posX+28, posY + 7,rightbg, fg, "▄▄▖");
		ansi(posX+28, posY + 8,rightbg, fg, "▀▀▘");
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
	int x, y;

	//{{{ activeBox
	x = 25; y = 3;
	activeBox(x, y, 55, 16, -3, -5);
	ansi(x +  7,y +  1, -3, colFG, "Hi, this is Shea, this is Shea's website!");
	ansi(x +  7,y +  3, -3, colFG, "My current projects are: ");
	ansi(x +  3,y +  4, -3, colFG, "→maintaining my email service set up through the");
	ansi(x +  2,y +  5, -3, colFG, "emailwizz scripts");
	ansi(x +  3,y +  6, -3, colFG, "→maintaining the matrix instance through synapse");
	ansi(x +  2,y +  7, -3, colFG, "     so i may have an account on my domain");
	ansi(x +  3,y +  8, -3, colFG, "     →maintaining the nginx server to serve these");
	ansi(x +  2,y +  9, -3, colFG, "objects that refer to my         projects");
	ansi(x +  3,y + 10, -3, colFG, "→creating these comfy~~           pages");
	ansi(x +  3,y + 11, -3, colFG, "→accomodating myself w             git");
	ansi(x +  2,y + 12, -3, colFG, "→kissin      my partner");

	//}}}

	//{{{ Shoru
	x = 1; y = 3;
	shoru(x, y, colBG, colBG, -3, -4);
	
	if(isTrueColor){
		ansi(x+24,y +  4, -5, -4, "▘");
		ansi(x+24,y + 11, -5, -4, "▖");
		ansi(x+24,y +  6, -5, -4, "▄");
		ansi(x+24,y +  9, -5, -4, "▀");
	}
	//}}}

	//{{{ indexCard
	x = 18;	y = 15;
	indexCard( x, y, 25, 10, -3, colBG, -3, -5);
	if(isTrueColor){
		ansi(x+7,15, -5, -5, "█");
		ansi(x+9,16, -3, -5, "▌");
		ansi(x+9,17, -3, -5, "▙");
	}
	else{
		ansi(x+7,15, -3, -5, "┴");
		ansi(x+25,18, -3, -5, "├");
	}
	ansi(x+ 3, y+2, -3, -5, "INDEX");
	ansi(x+18, y+2, -3, -5, "cURLs");
	for(int i=0; i<5; i++){
		ansi(x+2, y+4+i, -3, -10, "$");
		ansi(x+4, y+4+i, -3, -11, "curl");
		ansi(x+9, y+4+i, -3, -12, "she-a.eu");
	}
	ansi(x+17, y+4, -3, -13, "/simple");
	ansi(x+17, y+5, -3, -13, "/index");
	ansi(x+17, y+6, -3, -13, "/about");
	ansi(x+ 9, y+8, -3, -12, "sh      ");
	ansi(x+11, y+8, -3, -12, "\e[5m_     ");//}}}

	//{{{ socalBox
	x = 50; y = 12;
	SocialCard( x, y, 27, 13, -3, -3, -5);
	
	if(!isTrueColor){
		ansi(x,18, -3, -5, "┤");
		ansi(x+27,18, -3, -5, "├");
	}
	ansi(x+ 4, y+2, -3, -5, "     ");
	ansi(x+20, y+2, -3, -5, "     ");
	ansi(x+ 2, y+3, -3, -5, "socials");
	ansi(x+19, y+3, -3, -5, "contact");

	ansi(x+ 5,y+5,-3, -20, "libera");
	ansi(x+14,y+5,-3, -27, "/msg");
	ansi(x+19,y+5,-3, -97, "se-a");

	ansi(x+ 6,y+6,-3, -21, "email");
	ansi(x+15,y+6,-3, -97, "nu@she-a.eu");
	ansi(x+17,y+6,-3, -27, "@");

	ansi(x+ 5,y+7,-3, -22, "matrix");
	ansi(x+14,y+7,-3, -97, "@nu:she-a.eu");
	ansi(x+14,y+7,-3, -27, "@");
	ansi(x+17,y+7,-3, -27, ":");

	ansi(x+ 5,y+8,-3, -23, "github");
	ansi(x+14,y+8,-3, -97, "@nushea");
	ansi(x+14,y+8,-3, -27, "@");

	ansi(x+ 4,y+9,-3, -24, "bluesky");
	ansi(x+14,y+9,-3, -97, "@nu.she-a.eu");
	ansi(x+14,y+9,-3, -27, "@");

	ansi(x+ 4,y+10,-3, -25, "discord");
	ansi(x+14,y+10,-3, -97, "@.se.a");
	ansi(x+14,y+10,-3, -27, "@");

	ansi(x+3, y+11,-3, -26, "not fedi   @nu@she-a.eu");
	ranPage = 1;
	//}}}
} //}}}

void debug(){//{{{	
	char debugstring[BUFFER*4];
	sprintf(debugstring, "Domain: %s%s\nYer ip is: %s", host,uri, ip);
	ansi(1, HEIGH-2, colBG, colFG, debugstring);
	ranPage = 1;
}//}}}

void aboutPage(){ //{{{
	int x, y;

	//{{{ activeBox
	x = 25; y = 3;
	activeBox(x, y, 55, 16, -3, -5);
	ansi(x + 18,y +  1, -3, colFG, "Hi, this is Shea!!");
	ansi(x +  7,y +  3, -3, colFG, "I'm just a little girl of 22 years old that");
	ansi(x +  3,y +  4, -3, colFG, "likes doing all kinda unrelated stuff.");
	ansi(x +  3,y +  6, -3, colFG, "For one i know basic crochet and have rudimentary");
	ansi(x +  2,y +  7, -3, colFG, "     drawing skills, and know how to solve some");
	ansi(x +  2,y +  8, -3, colFG, "     rubix cubes like the 3x3, mirror and the skewb");
	ansi(x +  3,y +  9, -3, colFG, "I am like 1000ELO in chess and like plaing it on");
	ansi(x +  3,y + 10, -3, colFG, "long train rides.");
	ansi(x +  3,y + 11, -3, colFG, "I am part of the CYRA worldbuilding project altho");
	ansi(x +  5,y + 12, -3, colFG, "i need to participate          more        at it");
	ansi(x +  3,y + 13, -3, colFG, "I cant wait to live w             my            gf");

	//}}}

	//{{{ Shoru
	x = 1; y = 3;
	shoru(x, y, colBG, colBG, -3, -4);
	
	if(isTrueColor){
		ansi(x+24,y +  4, -5, -4, "▘");
		ansi(x+24,y + 11, -5, -4, "▖");
		ansi(x+24,y +  6, -5, -4, "▄");
		ansi(x+24,y +  9, -5, -4, "▀");
	}
	//}}}

	//{{{ indexCard
	x = 50;	y = 15;
	indexCard( x, y, 25, 10, -3, -3, -3, -5);
	if(isTrueColor){
		ansi(x+25,y+2, -3, -5, "▄");}
	else{
		ansi(x   ,18, -3, -5, "┤");
		ansi(x+25,18, -3, -5, "├");
	}
	for(int i=0; i<5; i++){
		ansi(x+2, y+4+i, -3, -10, "$");
		ansi(x+4, y+4+i, -3, -11, "curl");
		ansi(x+9, y+4+i, -3, -12, "she-a.eu");
	}
	ansi(x+17, y+4, -3, -13, "/simple");
	ansi(x+17, y+5, -3, -13, "/index");
	ansi(x+17, y+6, -3, -13, "/about");
	ansi(x+ 9, y+8, -3, -12, "sh      ");
	ansi(x+11, y+8, -3, -12, "\e[5m_     ");//}}}

	ranPage = 1;
}//}}}

void indexPage(){//{{{
	int x, y;

	//{{{ LEFTindexCard
	x = 22;	y = 3;
	indexCard( x, y, 28, 21, -3, colBG, colBG, -5);
	ansi(x+ 3, y+2, -3, -5, "INDEX");
	ansi(x+21, y+2, -3, -5, "cURLs");
	for(int i=0; i<16; i++){
		ansi(x+ 4, y+4+i, -3, -10, "$");
		ansi(x+ 6, y+4+i, -3, -11, "curl");
		ansi(x+11, y+4+i, -3, -12, "she-a.eu");
		ansi(x+19, y+4+i, -3, -5, "/test");
	}
	ansi(x+19,y+ 4, -3, -13, "     ");
	ansi(x+19,y+ 5, -3, -13, "/index");
	ansi(x+19,y+ 6, -3, -13, "/about");
	ansi(x+11,y+19, -3, -12, "sh           ");
	ansi(x+13,y+19, -3, -12, "\e[5m_");//}}}

	//{{{ RIGHTindexCard
	x = 50+isTrueColor;	y = 3;
	indexCard( x, y, 28, 21, -3, colBG, colBG, -5);
	if(!isTrueColor){
		ansi(x,y+2, -3, -5, "┬");
		ansi(x,y+19, -3, -5, "┴");
	}
	ansi(x+ 3, y+2, -3, -5, "INDEX");
	ansi(x+21, y+2, -3, -5, "cURLs");
	for(int i=0; i<16; i++){
		ansi(x+ 4, y+4+i, -3, -10, "$");
		ansi(x+ 6, y+4+i, -3, -11, "curl");
		ansi(x+11, y+4+i, -3, -12, "she-a.eu");
		ansi(x+19, y+4+i, -3, -5, "/s/test");
	}
	ansi(x+19,y+ 4, -3, -13, "/s     ");
	ansi(x+19,y+ 5, -3, -13, "/s/index");
	ansi(x+19,y+ 6, -3, -13, "/s/about");
	ansi(x+11,y+19, -3, -12, "sh             ");
	ansi(x+13,y+19, -3, -12, "\e[5m_");//}}}

	//{{{ Active box
	x = 1; y = 18;
	activeBox(x, y, 22, 6, -3, -5);
	if(!isTrueColor){
		ansi(x+21, y , -3, -5, "┤");
		ansi(x+21,y+4, -3, -5, "├");
	}
	ansi(x+10,y+1, -3, -5, "Hi,");
	ansi(x+4, y+2, -3, -5, "You can add /s/");
	ansi(x+4, y+3, -3, -5, "to any link you");
	ansi(x+7, y+4, -3, -5, "may want");
	//}}}

	//{{{ Shoru
	x = 1; y = 3;
	shoru(x, y, colBG, colBG, -3, -4);
	
	if(isTrueColor){
		ansi(x+24,y +  4, -3, -4, "▘");
		ansi(x+24,y + 11, -3, -4, "▖");
		ansi(x+24,y +  6, -3, -4, "▄");
		ansi(x+24,y +  9, -3, -4, "▀");
		ansi(x+23,y +  6, -3, -4, "▄");
		ansi(x+23,y +  9, -3, -4, "▀");
		ansi(x+22,y +  6, -3, -4, "▄");
		ansi(x+22,y +  9, -3, -4, "▀");
	}
	//}}}
	ranPage = 1;
}

//}}}

void PNFPage(){ //{{{
	int x, y;
	//{{{ Shoru
	x = 1; y = 3;
	shoru(x, y, colBG, colBG, colBG, -4);
	
	//}}}

	//{{{ indexCard
	x = 52;	y = 15;
	indexCard( x, y, 25, 10, -3, colBG, colBG, -5);
	for(int i=0; i<5; i++){
		ansi(x+2, y+4+i, -3, -10, "$");
		ansi(x+4, y+4+i, -3, -11, "curl");
		ansi(x+9, y+4+i, -3, -12, "she-a.eu");
	}
	ansi(x+17, y+4, -3, -13, "/simple");
	ansi(x+17, y+5, -3, -13, "/index");
	ansi(x+17, y+6, -3, -13, "/about");
	ansi(x+ 9, y+8, -3, -12, "sh      ");
	ansi(x+11, y+8, -3, -12, "\e[5m_     ");
	//}}}
	//{{{ Draw the cat ears
	x = 29; y = 3;
	ansi(x + 2,y     , colBG, -5,   "█▀▀▀▀▄▄             ▄▄▀▀▀█");
	ansi(x + 1,y +  1, colBG, -5,  "▄▀     ▀█▄        ▄█▀     ▀▄");
	ansi(x + 1,y +  2, colBG, -5,  "█        █        █        █");
	ansi(x    ,y +  3, colBG, -5, "█       ▄████████████▄       █");
	ansi(x    ,y +  4, colBG, -5, "█     ▄█▀            ▀█▄     █");
	ansi(x + 1,y +  5, colBG, -5,  "█▄  ▄▀                ▀▄  ▄█");
	ansi(x + 2,y +  6, colBG, -5,   "▀▀█                    █▀▀");
	ansi(x + 3,y +  7, colBG, -5,    "█                      █");
	ansi(x + 3,y +  8, colBG, -5,    "█      ERROR: 404      █");
	ansi(x + 3,y +  9, colBG, -5,    "█    Page not found    █");
	ansi(x + 3,y + 10, colBG, -5,    "█                      █");
	ansi(x + 4,y + 11, colBG, -5,     "█                    █");
	ansi(x + 5,y + 12, colBG, -5,      "▀▄                ▄▀");
	ansi(x + 6,y + 13, colBG, -5,       "▀█▄            ▄█▀");

	
	ansi(x+10, y+8, colBG, colFG,            "ERROR: 404");
	ansi(x+ 8, y+9, colBG, colFG,          "Page not found");
	ansi(67, 4, colBG, colFG,        "Sorry,");
	ansi(60, 5, colBG, colFG, "idk where i put this");
	ansi(68, 6, colBG, colFG,         "~^~");


//	ansi(34, 7, colBG, colFG, "Sorry, idk where i put this page ~^~ ");
//	ansi(45, 9, colBG, colFG,            "ERROR: 404");
//	ansi(43,10, colBG, colFG,          "Page not found");

	//}}}


	ansi(11,20, colBG, colFG,"You might want to go to one of these ->");

} //}}}


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
		if(!(strncmp(modifiedURI, "index", 5)))
			indexPage();
		if(!(strncmp(modifiedURI, "about", 5)))
			aboutPage();
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
			PNFPage();
		}
	}

	//}}}
	ansi(1, HEIGH-1, colBG, colFG, "\n");
	free(modifiedURIp);
}//}}}

