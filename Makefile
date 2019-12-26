.PHONY: all clean install

CFLAGS=-Wall -Wextra
name:= main
sources:= main.c
objects:= $(sources:.c=.o)
prefix:=/var/www
bindir:=$(prefix)/cgi-bin

all: $(name)

$(name): $(objects)

install: all
	install $(name) $(bindir)/$(name)

clean:
	rm -f $(name) $(objects)
