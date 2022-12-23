all: main.c
	gcc -g -Wall -o copysync main.c

clean:
	$(RM) copysync
