#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <mqueue.h>

int main()
{
	struct mq_attr attr;
	mqd_t mqserv, mqclien;

	char buff[256] = "client_side";

	attr.mq_maxmsg = 20;
	attr.mq_msgsize = 256;
	attr.mq_flags = 0;
	attr.mq_curmsgs = 0;

	if((mqserv = mq_open("/server_side", O_WRONLY) == -1))
		printf("Error1");

	if((mqclien = mq_open("/client_side", O_RDONLY | O_CREAT, 0666, &attr) == -1))
		printf("Error2");

	printf("Send message to server: ");
	scanf("%s", buff);
	
	if(mq_send(mqserv, buff, strlen(buff)+1, 1) == -1)
		printf("Error4");

	if(mq_receive(mqserv, buff, 256, NULL) == -1)
		printf("Error3");

	printf("Message recieved as: %s\n", buff);

	return 0;
}
