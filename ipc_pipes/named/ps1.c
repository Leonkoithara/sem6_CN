#include <stdio.h>

#define FIFO "/tmp/myfifo"

int main()
{
	FILE *fifo;
	char buff[256];

	fifo = fopen(FIFO, "r");

	fgets(buff, 255, fifo);

	printf("%s", buff);
	return 0;
}
