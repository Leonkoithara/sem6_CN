
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <mqueue.h>

int main()
{
	struct mq_attr attr;
	mqd_t mqserv, mqclien;

	char buff[66];

	bzero(&attr, sizeof(attr));
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = 25;
	attr.mq_flags = 0;
	attr.mq_curmsgs = 0;

	mqserv = mq_open("/server_side", O_RDONLY | O_CREAT, 0666, &attr);
	if(mqserv == -1)
		printf("Error1");

	if(mq_receive(mqserv, buff, 66, NULL) == -1)
		perror("error");

	return 0;
}
