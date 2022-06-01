CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -g -fsanitize=leak -fsanitize=address  -fsanitize=address
LDFLAGS=-lSDL2 -lm -O3
VPATH:=helpers/ board/ play/ n_tree/
all: tic_tac 
tic_tac: board.o helpers.o play.o tree.o main.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) 

helpers.o: helpers.h
board.o: board.h
tree.o: tree.h 
play.o: play.h 
run:
	./tic_tac
cls:
	clear
clean:
	rm -rf *.o tic_tac
	$(MAKE) cls

rebuild: 
	$(MAKE) clean 
	$(MAKE) tic_tac