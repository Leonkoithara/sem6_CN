#include <semaphore.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int shm_fd1, shm_fd2, shm_fd3, shm_fd4, shm_fd5;
	sem_t *wlock;
	int *readers, *ptr;

	shm_fd1 = shm_open("mem_seg1", O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd1, sizeof(int));
	shm_fd2 = shm_open("mem_seg2", O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd2, sizeof(int));
	shm_fd3 = shm_open("wlock", O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd3, sizeof(sem_t));
		
	ptr = (int*)mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd1, 0);
	if(ptr == MAP_FAILED)
		printf("ptr map failed");
	readers = (int*)mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd2, 0);
	if(readers == MAP_FAILED)
		printf("readers map failed");
	wlock = (sem_t*)mmap(0, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd3, 0);
	if(wlock == MAP_FAILED)
		printf("wlock map failed");

	sem_init(wlock, 1, 1);
	*readers = 0;
	*ptr = 2;

	while(1)
	{
		sleep(10);
	}

	return 0;
}
