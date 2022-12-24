prefix=/usr/local

all: main.c
	gcc -g -Wall -o copyfsync main.c

clean:
	$(RM) copyfsync


uninstall:
	rm $(prefix)/bin/copyfsync

install: copyfsync
	install -m 0755 copyfsync $(prefix)/bin

.PHONY: install
