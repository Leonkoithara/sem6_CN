#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORTNO 8080

int main()
{
	struct sockaddr_in serv_addr, clien_addr;
	int sockfd, newsockfd, clientlen, n;
	char buff[256];
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd  < 0)
		perror("Error1");

	bzero(&serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORTNO);
	serv_addr.sin_addr.s_addr = INADDR_ANY;					//ip of server

	if(bind(sockfd,(const struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
		perror("Error2");

	listen(sockfd, 5);

	clientlen = sizeof(clien_addr);
	newsockfd = accept(sockfd, (struct sockaddr*)&clien_addr,(socklen_t*)&clientlen);
	if(newsockfd < 0)
		perror("Error3");

	bzero(buff, 256);
	n = read(newsockfd, buff, 255);
	if(n < 0)
		printf("Error4");
	printf("Message Recieved as: %s\n", buff);

	return 0;
}
