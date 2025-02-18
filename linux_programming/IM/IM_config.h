#ifndef IM_CONFIG_H
#define IM_CONFIG_H

#define MQ_SERVER "/mqs"

#define CLIENTS_LIMIT 5
#define MESSAGE_LIMIT 1000
#define CLIENT_NAME_LIMIT 20

#include <mqueue.h>

extern char MQ_CLIENTS[CLIENTS_LIMIT][CLIENT_NAME_LIMIT];

typedef struct {
	int from;
	int to;
	char message[MESSAGE_LIMIT];
} Payload;


int create_server_mq(mqd_t *server, int permissions);
int create_clients_mq(mqd_t *clients, int permissions);

#endif // IM_CONFIG_H

