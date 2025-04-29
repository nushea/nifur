#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 0x400
#define WIDTH 80
#define HEIGH 24

#define colBG -1
#define colFG -2

void debug();

char uri[BUFFER], host[BUFFER], ip[BUFFER];
int isTrueColor;

int colmap(int color){
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
}

void ansi(int posX, int posY, int bg, int fg, char * output){ //{{{
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
			sprintf(oup, "\x1b[%i;%iH\x1b[38;2;%i;%i;%i;48;2;%i;%i;%im%s\x1b[0m", posY, posX, fg/0x10000, (fg/0x100)%0x100, fg%0x100, bg/0x10000, (bg/0x100)%0x100, bg%0x100, output);
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
	sprintf(oup, "\x1b[%i;%iH\x1b[%i;%im%s\x1b[0m", posY, posX, fg, bg, output);
	printf("%s", oup);
	free(oup);
		
} //}}}

void trueColorInit(){//{{{
	for(int i=1; i<=HEIGH; i++)
		for(int j=1; j<=WIDTH; j++)
			if((i+j)%2)
				ansi(j, i, -1, 0xb4befe, " ");
			else
			 	ansi(j, i, -1, 0x45475a, " ");
	ansi(1,1, colBG, colFG, "curl?? :3\n");
	printf("\x1b[%i;%iH\x1b[0\n", HEIGH, WIDTH+1);

}//}}}

void simlColorInit(){ //{{{
	for(int i=1; i<=HEIGH; i++)
		for(int j=1; j<=WIDTH; j++)
			if((i+j)%2)
				dots(j, i, -1, 91, " ");
			else
			 	dots(j, i, -1, 92, " ");
	dots(1,1, colBG, colFG, "curl?? :3\n");
	printf("\x1b[%i;%iH\x1b[0\n", HEIGH, WIDTH+1);
} //}}}

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

	if(!(strncmp(uri, "/debug", 7))){
		debug();
		return 0;
	}
	printf("\x1b[2J");
	if(isTrueColor)
		trueColorInit();
	else
	 	simlColorInit();
//	printf("truecol=%i\n", isTrueColor);
}

void debug(){	
	printf("Domain: %s%s\nYer ip is: %s\n", host,uri, ip);
}
