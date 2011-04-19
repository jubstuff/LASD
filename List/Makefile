CC = gcc
CFLAGS = -Wall -g
OBJS = lista.o operazioni_numeri.o

lista-generale.out : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) src/main.c -o bin/lista-generale.out
lista.o : src/lista.c src/lista.h
	$(CC) $(CFLAGS) -c src/lista.c
operazioni_numeri.o : helpers/operazioni_numeri.c helpers/operazioni_numeri.h
	$(CC) $(CFLAGS) -c helpers/operazioni_numeri.c 
clean :
	rm $(OBJS) lista-generale.out
