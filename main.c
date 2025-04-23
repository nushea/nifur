#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 0x100


int main(){
    printf("Content-Type: text/plain\n\n");
	if(!(getenv("REQUEST_URI")&&getenv("SERVER_NAME"))){
		printf("freaky ahh request\n");
		return -1;
	}
	char uri[BUFFER], host[BUFFER];
	strncpy(uri, getenv("REQUEST_URI"), BUFFER);
	strncpy(host, getenv("SERVER_NAME"), BUFFER);
	
	printf("domain: %s%s\n", host,uri);
}
