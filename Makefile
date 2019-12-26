.PHONY: all clean install

CFLAGS=-Wall -Wextra
project:=bulletin
name:= index.cgi
sources:= index.c
objects:= $(sources:.c=.o)
prefix:=/var/www/$(project)
bindir:=$(prefix)

all: $(name)

$(name): $(objects)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

install: all
	install $(name) $(bindir)/$(name)
	chcon -t httpd_sys_script_exec_t $(bindir)/$(name)

clean:
	rm -f $(name) $(objects)
