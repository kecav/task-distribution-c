CC = gcc
CFLAGS = -Wall -Wextra

SERVER_SRC = ./Server/server.c
CLIENT_SRC = ./Client/client.c

SERVER_TARGET = ./Server/server
CLIENT_TARGET = ./Client/client

.PHONY: all clean

all: $(SERVER_TARGET) $(CLIENT_TARGET)

$(SERVER_TARGET): $(SERVER_SRC)
	$(CC) $(CFLAGS) $^ -o $@

$(CLIENT_TARGET): $(CLIENT_SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(SERVER_TARGET) $(CLIENT_TARGET)
