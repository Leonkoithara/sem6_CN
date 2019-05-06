#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <sys/wait.h>

int main()
{
	FILE *fp;
	int fd[2], pid, n=0;
	char buff[256];

	if(pipe(fd) < 0)
		perror("pipe err\n");

	pid = fork();

	if(pid < 0)
		printf("Error\n");
	else if(pid == 0)
	{
		close(fd[0]);
		printf("Enter message: ");
		fgets(buff, 256, stdin);
		write(fd[1], buff, 256);
	}
	else if(pid > 0)
	{
		close(fd[1]);
		bzero(buff, 256);

		wait(NULL);

		n = read(fd[0], buff, 256);
		if(n > 0)
			printf("\nMessage recieved: %s\n", buff);
	}

	return 0;
}
