CC=gcc
CFLAGS=-lpthread -Wall -Wextra


all: clientService.o main.o Options.o serverService.o showConnections.o StringProcess.o Connecta.o GestorMissatge.o
	$(CC) clientService.o main.o Options.o serverService.o showConnections.o StringProcess.o Connecta.o GestorMissatge.o -o Trinity $(CFLAGS)

clientService.o: clientService.c
	$(CC)  clientService.c -c $(CFLAGS)

main.o: main.c
	$(CC)  main.c -c $(CFLAGS)

Options.o: Options.c
	$(CC)  Options.c -c $(CFLAGS)

serverService.o: serverService.c
	$(CC)  serverService.c -c $(CFLAGS)

showConnections.o: showConnections.c
	$(CC)  showConnections.c -c $(CFLAGS)

StringProcess.o: StringProcess.c
	$(CC)  StringProcess.c -c $(CFLAGS)

Connecta.o: Connecta.c
	$(CC)  Connecta.c -c $(CFLAGS)

GestorMissatge.o: GestorMissatge.c
	$(CC)  GestorMissatge.c -c $(CFLAGS)
