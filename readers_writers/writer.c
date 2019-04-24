#include <semaphore.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int shm_fd1, shm_fd2, shm_fd3;

	int *ptr, *readers;
	sem_t *wlock;
	
	shm_fd1 = shm_open("mem_seg1", O_RDWR, 0666);
	shm_fd2 = shm_open("mem_seg2", O_RDWR, 0666);
	shm_fd3 = shm_open("wlock", O_RDWR, 0666);

	ptr = (int*)mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd1, 0);
	if(ptr == MAP_FAILED)
		printf("ptr map failed");
	readers = (int*)mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd2, 0);
	if(readers == MAP_FAILED)
		printf("readers map failed");
	wlock = (sem_t*)mmap(0, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd3, 0);
	if(wlock == MAP_FAILED)
		printf("wlock map failed");

	while(1)
	{ 
		if(*readers == 0)
		{
			sem_wait(wlock);
			*ptr = 2*(*ptr) - 1;
			printf("Written: %d\n", *ptr);
			sem_post(wlock);
		}
		sleep(3);
	}
	return 0;
}
