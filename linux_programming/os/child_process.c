#include <stdio.h>
#include <unistd.h>

#include <sys/wait.h>

int main() {
	printf("Common area.\n");
	pid_t pid;
	if ((pid = fork()) < 0) {
		printf("Failed to create child process.\n");
		return 1;
	}
	if (pid == 0) { // child process
		for (int i = 0; i < 10; ++i) {
			printf("I am the child.\n");
			fflush(stdout);
		}
	} else { // parent process
		for (int i = 0; i < 10; ++i) {
			printf("My child is %ld.\n", pid);
			fflush(stdout);
			wait(NULL);
		}
	}
	return 0;
}

