//Includes 
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

//Prototypes

int main()
{
	int shm_fd1, shm_fd2, shm_fd3;

	int *ptr, *flag;
	sem_t *sem;

	shm_fd1 = shm_open("mem_seg1", O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd1, sizeof(int));
	shm_fd2 = shm_open("mem_seg2", O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd2, sizeof(int));
	shm_fd3 = shm_open("sem_shared", O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd3, sizeof(sem_t));

	ptr = (int*)mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd1, 0);
	if(ptr == MAP_FAILED)
		printf("map1 failed");

	flag = (int*)mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd2, 0);
	if(flag == MAP_FAILED)
		printf("map2 failed");

	sem = (sem_t*)mmap(0, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd3, 0);
	if(sem == MAP_FAILED)
		printf("map3 failed");

	sem_init(sem, 1, 1);
	*ptr = 0;
	*flag = 0;
	
	for(;;)
	{
		if(*flag == 0)
		{
			sem_wait(sem);
			(*ptr)++;
			printf("%d\n", *ptr);
			sem_post(sem);
			*flag = 1;
			sleep(1);
		}
		else
			sleep(1);
	}

	return 0;
}

//Definitions
