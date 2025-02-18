#include "IM_config.h"


char MQ_CLIENTS[CLIENTS_LIMIT][CLIENT_NAME_LIMIT] = {
	"/mqc1",
	"/mqc2",
	"/mqc3",
	"/mqc4",
	"/mqc5"
};


int create_server_mq(mqd_t *server, int permissions)
{
	*server = mq_open(MQ_SERVER, permissions);
	return *server == (mqd_t)(-1);
}


/**
 * @returns
 * Returns 0 if all the mqds were created.
 * Else returns the number of mqd which could not be
 * created.
 */
int create_clients_mq(mqd_t *clients, int permissions)
{
	for (int i = 0; i < CLIENTS_LIMIT; ++i) {
		clients[i] = mq_open(MQ_CLIENTS[i], permissions);
		if (clients[i] != (mqd_t)(-1)) continue;
		// unlink previously created mq
		for (int j = 0; j < i; ++j)
			mq_unlink(MQ_CLIENTS[j]);
		return i + 1;
	}
	return 0;
}

