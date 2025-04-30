#include "printers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void debug();

char uri[BUFFER], host[BUFFER], ip[BUFFER];

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
	ansi(1,1, colBG, -3, "$");
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

int main(){
	//{{{ Pre-reqs
    printf("Content-Type: text/plain\n\n");
	if(!(getenv("REQUEST_URI")&&getenv("SERVER_NAME")&&getenv("REMOTE_ADDR"))){
		printf("freaky ahh request\n");
		return -1;
	}
	
	strncpy(uri, getenv("REQUEST_URI"), BUFFER); uri[BUFFER-1] = '\0';
	strncpy(host, getenv("SERVER_NAME"), BUFFER); host[BUFFER-1] = '\0';
	strncpy(ip, getenv("REMOTE_ADDR"), BUFFER); ip[BUFFER-1] = '\0';
	isTrueColor = 1;

	if(!(strncmp(uri, "/simpl", 7))){
		isTrueColor = 0;
	}
	//}}}

	initProc();
	if(!(strncmp(uri, "/debug", 7))){
		debug();
		return 0;
	}
//	printf("truecol=%i\n", isTrueColor);
}

void debug(){	
	char debugstring[BUFFER];
	sprintf(debugstring, "Domain: %s%s\nYer ip is: %s", host,uri, ip);
	ansi(1, HEIGH-2, colBG, colFG, debugstring);
}
