#include <fcntl.h>
#include <stdio.h>
#include <mqueue.h>

#include "IM_config.h"

mqd_t server;
Payload payload;
mqd_t clients[CLIENTS_LIMIT];


int forward_messages()
{
	int length = mq_receive(server, (char *)&payload, sizeof(Payload), NULL);
	if (length == 0) return 1;
	int status = mq_send(clients[payload.to], (char *)&payload, sizeof(Payload), 1);
	return status;
}

void unlink_server_queue()
{
	mq_unlink(MQ_SERVER);
}

void unlink_client_queues()
{
	for (int i = 0; i < CLIENTS_LIMIT; ++i)
		mq_unlink(MQ_CLIENTS[i]);
}


int main()
{
	int status;
	/*
	unlink_server_queue();
	if (create_server_mq(&server, O_CREAT | O_RDONLY) != 0) {
		printf("Cannot create %s.\n", MQ_SERVER);
		return 0;
	}
	unlink_client_queues();
	if ((status = create_clients_mq(clients, O_CREAT | O_WRONLY)) != 0) {
		printf("Cannot create %s.\n", MQ_CLIENTS[status - 1]);
		return 0;
	}
	*/
	create_server_mq(&server, O_CREAT | O_RDONLY);
	create_clients_mq(clients, O_CREAT | O_WRONLY);
	while (1) {
		if (forward_messages() == 0)
			printf("Forwarded message from %d to %d.\n", payload.from, payload.to);
	}
	return 0;
}

