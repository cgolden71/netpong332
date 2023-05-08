CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: net_pong

net_pong: main.o game.o sppbtp.o
	$(CC) $(CFLAGS) main.o game.o sppbtp.o -o net_pong -lncurses

main.o: main.c game.h sppbtp.h
	$(CC) $(CFLAGS) -c main.c -o main.o

game.o: game.c game.h
	$(CC) $(CFLAGS) -c game.c -o game.o

sppbtp.o: sppbtp.c sppbtp.h
	$(CC) $(CFLAGS) -c sppbtp.c -o sppbtp.o

clean:
	rm -f net_pong main.o game.o sppbtp.o
