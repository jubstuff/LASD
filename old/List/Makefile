CC = gcc
CFLAGS = -Wall -g
OBJS = lista.o gestione_citta.o

lista-generale.out : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) src/main.c -o bin/lista-generale.out
lista.o : src/lista.c src/lista.h
	$(CC) $(CFLAGS) -c src/lista.c
gestione_citta.o : helpers/gestione_citta.c helpers/gestione_citta.h
	$(CC) $(CFLAGS) -c helpers/gestione_citta.c 
clean :
	rm $(OBJS) lista-generale.out
