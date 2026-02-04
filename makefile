CC = gcc
CFLAGS = -g
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

prog: main.o
	$(CC) main.o -o prog $(LIBS) $(CFLAGS)

main.o: main.c
	$(CC) -c main.c $(CFLAGS)

clean:
	rm -f *.o prog



