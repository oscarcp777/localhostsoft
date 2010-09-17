OBJECTS=session.o queries.o parsing.o format.o objects.o libspopc.o mutex.o
CFLAGS= -Wall -Wextra -pedantic -pipe -fPIC -Os -DUSE_SSL -D_REENTRANT -DUSE_SEM
LDFLAGS=-lssl -lcrypto -lrt
all : libspopc.a gmail-poptest.c
	$(CC) gmail-poptest.c -o gmail-poptest $(CFLAGS) $< -L. -lspopc $(LDFLAGS)
