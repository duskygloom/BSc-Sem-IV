#include <fcntl.h>
#include <stdio.h>
#include <mqueue.h>
#include <string.h>

#include "IM_config.h"

Payload payload;

char buffer[MESSAGE_LIMIT];

mqd_t server;


/**
 * @returns
 * Returns 0 if successful.
 */
int send_message(int from, int to)
{
	payload.from = from;
	payload.to = to;
	strcpy(payload.message, buffer);
	int status = mq_send(server, (char *)&payload, sizeof(Payload), 1);
	return status;
}


int get_line()
{
	int length = 0, ch;
	while (length < MESSAGE_LIMIT && (ch = getchar()) != '\n')
		buffer[length++] = ch;
	return length;
}


void prompt()
{
	int from, to;
	printf("From, to: ");
	scanf("%d %d", &from, &to);
	printf("Message: ");
	get_line();
	int status = send_message(from, to);
	if (status == 0)
		printf("Sent successfully to %d.\n\n", payload.to);
	else
		printf("Could not send.\n\n");
}


int main()
{
	/*
	int status = create_server_mq(&server, O_WRONLY);
	if (status != 0) {
		printf("Could not connect to %s.\n", MQ_SERVER);
		return 0;
	}
	*/
	create_server_mq(&server, O_WRONLY);
	while (1)
		prompt();
	return 0;
}

