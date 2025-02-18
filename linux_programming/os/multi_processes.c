#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/mman.h>
#include <sys/wait.h>

#define SHM_NAME "/comm.duskygloom.multiproc"
#define SIZE 1024

long sum = 0;

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: ./a.out <number>\n");
		return 1;
	}

	pid_t pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Failed to fork.\n");
		return 2;
	}

	char *buffer;
	
	int n = atoi(argv[1]);

	int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
	ftruncate(fd, SIZE);
	
	if (pid == 0) { // child process
		for (int i = n/2; i <= n; ++i) {
			sum += i;
			putchar('!');
			fflush(stdout);
		}
		buffer = mmap(buffer, SIZE, PROT_READ, MAP_SHARED, fd, 0);
		printf("\nWaiting for parent...\n");
		while (*buffer != 'P'); // waiting for message from parent
		long parent_sum = atol(buffer+2); // message = P:message
		printf("Child says: %ld + %ld\n", sum, parent_sum);
		buffer = mmap(buffer, SIZE, PROT_WRITE, MAP_SHARED, fd, 0);
		sprintf(buffer, "C:%ld", sum);
		sum += parent_sum;
	} else { // parent process
		for (int i = 0; i < n/2; ++i) {
			sum += i;
			putchar('.');
			fflush(stdout);
		}
		buffer = mmap(buffer, SIZE, PROT_WRITE, MAP_SHARED, fd, 0);
		sprintf(buffer, "P:%ld", sum);
		buffer = mmap(buffer, SIZE, PROT_READ, MAP_SHARED, fd, 0);
		printf("\nWaiting for child...\n");
		while (*buffer != 'C');
		long child_sum = atol(buffer+2);
		printf("Parent says: %ld + %ld\n", sum, child_sum);
		sum += child_sum;
		wait(NULL);
		shm_unlink(SHM_NAME);
	}

	printf("\nSum: %ld\n", sum);
	return 0;
}

