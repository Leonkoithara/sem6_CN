#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <mqueue.h>
#include <sys/types.h>

int main()
{
	struct mq_attr attr;
	mqd_t mqserv, mqclien;

	char buff[256] = "server_side";

	attr.mq_maxmsg = 20;
	attr.mq_msgsize = 256;
	attr.mq_flags = 0;
	attr.mq_curmsgs = 0;
	
	mqserv = mq_open("/server_side", O_RDONLY | O_CREAT, 0666, &attr);
	if(mqserv == -1)
		perror("Error1");

	if(mq_receive(mqserv, buff, 256, NULL) == -1)
		perror("Server: mq_receive");

	printf("Message recieved as: %s\n", buff);
	printf("Send message to client: ");
	scanf("%s", buff);
	
	if((mqclien = mq_open("/client_side", O_WRONLY) == -1))
		printf("Error3");

	if(mq_send(mqclien, buff, strlen(buff)+1, 1) == -1)
		printf("Error4");

	printf("Response sent to client...\n");

	return 0;
}
