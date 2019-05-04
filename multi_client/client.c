#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#define PORTNO 8080

int main()
{
	struct sockaddr_in serv_addr;
	struct hostent *server;
	int sockfd, n; 
	char buff[256];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		perror("Error1");

	server = gethostbyname("192.168.1.110");
	if(server == NULL)
		perror("Error2");

	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy(server->h_addr,&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(PORTNO);

	if(connect(sockfd, (const struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
		perror("Error3");

	while(1)
	{
		printf("Enter message: ");
		gets(buff);
		n = write(sockfd, buff, strlen(buff));
		if(n < 0)
			printf("Error4");
	}

	return 0;
}
