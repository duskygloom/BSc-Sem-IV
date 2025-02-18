CC		= gcc
ARGS	= -Wall -g -lrt
BUILD	= build
BINARY	= app
OBJECTS = $(BUILD)/IM_config.o $(BUILD)/IM_server.o $(BUILD)/IM_client_reader.o $(BUILD)/IM_client_writer.o

all: init $(OBJECTS) server client_reader client_writer

$(BUILD)/%.o: %.c
	$(CC) $^ -o $@ $(ARGS) -c

server: $(BUILD)/IM_config.o $(BUILD)/IM_server.o
	$(CC) $^ -o $@ $(ARGS)

client_reader: $(BUILD)/IM_config.o $(BUILD)/IM_client_reader.o
	$(CC) $^ -o $@ $(ARGS)

client_writer: $(BUILD)/IM_config.o $(BUILD)/IM_client_writer.o
	$(CC) $^ -o $@ $(ARGS)

init:
	mkdir -p $(BUILD)

clean:
	rm -f $(BUILD)/*

run:
	./server &
	./client_writer &
	./client_reader

