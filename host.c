#include <stdio.h>


#include "host.h"


void host_send(int sock)
{
    const char *buf = "host send : rfnsol ";
	printf("host_send~\n");
	
	send(sock, buf, strlen(buf), 0);		


	printf("~host_send\n");

	while(1)
		{
		}
}





