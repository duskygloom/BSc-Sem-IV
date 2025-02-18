#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long sum = 0;

void *runner(void *params) {
	int n = atoi(((char **)params)[0]);
	for (int i = n/2; i <= n; ++i) {
		sum += i;
		putchar('!');
		fflush(stdout);
	}
	pthread_exit(0);
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: ./a.out <number>\n");
		return 1;
	}
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr); // load default thread attrs
	pthread_create(&tid, &attr, runner, argv+1);
	int n = atoi(argv[1]);
	for (int i = 0; i < n/2; ++i) {
		sum += i;
		putchar('.');
		fflush(stdout);
	}
	pthread_join(tid, NULL);
	printf("\nSum: %ld\n", sum);
	return 0;
}

