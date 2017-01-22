default: server_client

CC?=gcc
CFLAG?= -w -pthread -O3

server_client: server_client.c
	$(CC) $< $(CFLAG) -o $@
