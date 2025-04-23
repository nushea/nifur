#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 0x100

int main(){
    printf("Content-Type: text/plain\n\n");
	if(!(getenv("REQUEST_URI")&&getenv("SERVER_NAME")&&getenv("REMOTE_ADDR"))){
		printf("freaky ahh request\n");
		return -1;
	}
	char uri[BUFFER], host[BUFFER], ip[BUFFER];
	strncpy(uri, getenv("REQUEST_URI"), BUFFER); uri[BUFFER-1] = '\0';
	strncpy(host, getenv("SERVER_NAME"), BUFFER); host[BUFFER-1] = '\0';
	strncpy(ip, getenv("REMOTE_ADDR"), BUFFER); ip[BUFFER-1] = '\0';
	
	printf("Domain: %s%s\nYer ip is: %s\n", host,uri, ip);
}
