#include "client.h"

int main(int argc, char **argv)
{
	int sockfd;
	char tcom[100];

	if(argc!=3){syserror("myc <IPaddress> <port>");}
        
        sockfd = client(argv[1], atoi(argv[2]));
        Recvmsg(tcom, sockfd); 
	
        if(strcmp(tcom, "connect ok"))
	{
		puts(tcom);
		syserror("link server exception.");
	}
	printf("link state:%s\n", tcom);
	return 0;
}

