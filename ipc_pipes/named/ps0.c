#include <stdio.h>
#include <sys/stat.h>

#define FIFO "/tmp/myfifo"

int main()
{
	FILE *fifo;
	char buff[256];

	if(mkfifo(FIFO, 0666) == -1)
		perror("err fifo\n");
	
	fifo = fopen(FIFO, "w");
	
	fgets(buff, 255, stdin);
	fprintf(fifo, "%s\n", buff);

	return 0;
}
