CC = gcc
CFLAGS = -Wall -g
OBJS = lista.o

lista-generale.out : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) src/main.c -o bin/lista-generale.out
lista.o : src/lista.c src/lista.h
	$(CC) $(CFLAGS) -c src/lista.c
clean :
	rm $(OBJS) lista-generale.out
