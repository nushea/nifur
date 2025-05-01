#include "printers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void debug();

char uri[BUFFER], host[BUFFER], ip[BUFFER], * modifiedURI, * modifiedURIp;
int ranPage = 0;

void trueColorInit(){//{{{
	for(int i=1; i<=HEIGH; i++)
		for(int j=1; j<=WIDTH; j++)
			if((i+j)%2)
				truc(j, i, -1, 0xb4befe, " ");
			else
			 	truc(j, i, -1, 0x45475a, " ");
}//}}}

void simlColorInit(){ //{{{
	for(int i=1; i<=HEIGH; i++)
		for(int j=1; j<=WIDTH; j++)
			if((i+j)%2)
				dots(j, i, -1, 37, " ");
			else
			 	dots(j, i, -1, 90, " ");
} //}}}

void initProc(){ //{{{ The default displaying present on every page
	printf("\x1b[2J");
	if(isTrueColor)
		trueColorInit();
	else
	 	simlColorInit();
	int space = 8;
	ansi(1,1, colBG, -32, "$");
	ansi(3,1, colBG, -4, "curl");
	
	ansi(space,1, colBG, -5, host);
	space += strlen(host);
	ansi(space,1, colBG, -6, uri);
	space += strlen(uri);

	if(space < WIDTH-49)
		ansi((WIDTH-space-20)/2 + space - 14,1,colBG, colFG, "World's most boring trannie!");
	
	ansi(WIDTH-20,1,colBG, colFG, "(minimum size: 80x24)");
	printf("\x1b[%i;%iH\x1b[0\n", HEIGH, WIDTH+1);
}//}}}

void indexCard(int posX, int posY, int sizX, int sizY, int bg, int fg){ //{{{
	if(sizX < 20 || sizY < 6 || sizX+posX > 80 || sizY+posY > 24){
		ansi(posX, posY, colBG, colFG, "indexCard sizes X:20-80 Y:7-24");
		return;}

	if(isTrueColor){ //{{{
		ansi(posX+ 5,posY+ 0, colBG,   fg,      "▄▄▄▄");
		ansi(posX+ 2,posY+ 1, colBG,   fg,   "▄▟▀▀  ▝▌");
		ansi(posX+ 4,posY+ 1,    bg,   fg,     "▀▀  ▝");
		ansi(posX   ,posY+ 2, colBG,   fg, "▗▛▘  ──┐ ▙");
		ansi(posX+ 1,posY+ 2,    bg,   fg,  "▛▘  ──┐ ");
		ansi(posX   ,posY+ 3, colBG,   fg, "▟");

		int overSize = 20;
		char over[BUFFER];
		memset(over, 0, BUFFER);
		strcpy(over, "▄");
		while(overSize < sizX){
			strcat(over, "▄");
			overSize+=1;
		}
		ansi(posX+overSize- 8,posY + 0, colBG, fg, "▄▄▄▄");
		ansi(posX+overSize- 9,posY + 1, colBG, fg,"▐▘  ▀▀▙▄");
		ansi(posX+overSize- 8,posY + 1,    bg, fg, "▘  ▀▀");
		ansi(posX+overSize- 9,posY + 2, colBG, fg,"▟ ┌──  ▝▜▖");
		ansi(posX+overSize- 8,posY + 2,    bg, fg," ┌──  ▝▜");
		ansi(posX+overSize   ,posY + 3, colBG, fg,        "▙");

		ansi(posX+10,posY+ 2, colBG,   fg, over);

		int ofy = 3;
		char background[80];
		memset(background, ' ', sizX-1);
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

void basicPage(){ //{{{
//	ansi(2, 2, colBG, colFG, "basic page");
	indexCard( 3, 3, 30, 21, -3, colFG);
	//activeBox( 1, 3, 80, 21, -3, colFG);
	
	ranPage = 1;
} //}}}

int main(){ //{{{
	//{{{ Pre-reqs
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
	if(!ranPage){
		if(tokenCount<=0){
			basicPage();
		}
		else{
			ansi(2, 2, colBG, colFG, "himitsu :3");
		}
	}

	//}}}
	ansi(1, HEIGH-2, colBG, colFG, "\n");
	free(modifiedURI);
}//}}}

void debug(){//{{{	
	char debugstring[BUFFER*4];
	sprintf(debugstring, "Domain: %s%s\nYer ip is: %s", host,uri, ip);
	ansi(1, HEIGH-2, colBG, colFG, debugstring);
	ranPage = 1;
}//}}}
