#include <fcntl.h>
#include <stdio.h>
#include <mqueue.h>
#include <string.h>

#include "IM_config.h"

Payload payload;

char buffer[MESSAGE_LIMIT];
mqd_t clients[CLIENTS_LIMIT];


/**
 * @returns
 * Returns the number of messages sent.
 */
int store_messages()
{
	int sent = 0;
	for (int i = 0; i < CLIENTS_LIMIT; ++i) {
		int length = mq_receive(clients[i], (char *)&payload, sizeof(Payload), NULL);
		if (length == 0) continue;
		// creating file name
		strcpy(buffer, ".");
		strcat(buffer, MQ_CLIENTS[i]);
		strcat(buffer, ".txt");
		// open file
		FILE *fp = fopen(buffer, "a");
		fprintf(fp, "%d sent: %s\n", payload.from, payload.message);
		fclose(fp);
		++sent;
	}
	return sent;
}


int main()
{
	/*
	int status = create_clients_mq(clients, O_RDONLY);
	if (status != 0) {
		printf("Could not connect to %s.\n", MQ_CLIENTS[status - 1]);
		return 0;
	}
	*/
	create_clients_mq(clients, O_RDONLY);
	while (1) {
		int sent = store_messages();
		if (sent > 0)
			printf("Sent %d messages.\n", sent);
	}
	return 0;
}

