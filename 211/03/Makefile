CC = gcc
CFLAGS = -ansi -Wall -pedantic
LIBALLEG = -L/usr/lib -lalleg-4.2.2
OBJS = fisica.o item.o oceano.o grafico.o colisao.o


jogo: fisica.o item.o oceano.o grafico.o colisao.o
	$(CC) $(CFLAGS) $(OBJS) $(LIBALLEG) -D_POSIX_C_SOURCE=199309L -lm jogo.c -o jogo

fisica.o: item.h fisica.h oceano.h
	$(CC) $(CFLAGS) -c $(LIBALLEG) -lm fisica.c

colisao.o: item.h fisica.h oceano.h colisao.h
	$(CC) $(CFLAGS) -c $(LIBALLEG) -lm colisao.c

grafico.o: item.h fisica.h oceano.h grafico.h
	$(CC) $(CFLAGS) -c $(LIBALLEG) -lm grafico.c

item.o: item.h
	$(CC) $(CFLAGS) -c $(LIBALLEG) item.c

oceano.o: oceano.h item.h fisica.h colisao.h
	$(CC) $(CFLAGS) -c $(LIBALLEG) oceano.c

clean: 
	rm *.o jogo

