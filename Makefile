all:
	cc -c *.c -Wall -ggdb -lm
	cc *.o -lm
