#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define SIZE 4096
#define SHM_NAME "/shared.duskygloom.moe"

void main() {
	int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
	ftruncate(fd, SIZE);
	char *buffer;
	pid_t pid;
	if ((pid = fork()) < 0) {
		fprintf(stderr, "Failed to create child process.");
		return;
	}
	if (pid == 0) { // child process
		buffer = mmap(buffer, SIZE, PROT_WRITE, MAP_SHARED, fd, 0);
		char *message = "C:Hello parent";
		sprintf(buffer, "%s", message);
		printf("Child wrote: %s\n", message);
		fflush(stdout);
		buffer = mmap(buffer, SIZE, PROT_READ, MAP_SHARED, fd, 0);
		printf("Child waiting for message...\n");
		fflush(stdout);
		while (*buffer != 'P');
		printf("Child read: %s\n", buffer);
		fflush(stdout);
	} else { // parent process
		buffer = mmap(buffer, SIZE, PROT_READ, MAP_SHARED, fd, 0);
		printf("Parent waiting for message...\n");
		fflush(stdout);
		while (*buffer != 'C');
		printf("Parent read: %s\n", buffer);
		fflush(stdout);
		buffer = mmap(buffer, SIZE, PROT_WRITE, MAP_SHARED, fd, 0);
		char *message = "P:Hi child";
		sprintf(buffer, "%s", message);
		printf("Parent wrote: %s\n", message);
		fflush(stdout);
		wait(NULL);
		shm_unlink(SHM_NAME);
	}
}

