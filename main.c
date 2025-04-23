#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 0x100


int main(){
    printf("Content-Type: text/plain\n\n");
	if(!getenv("REQUEST_URI")){
		printf("freaky ahh request\n");
		return -1;
	}
	char uri[BUFFER];
	strncpy(uri, getenv("REQUEST_URI"), BUFFER);
	
	printf("domain: %s\n", uri);
}
