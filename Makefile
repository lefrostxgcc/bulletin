.PHONY: all clean install

CFLAGS=-Wall -Wextra `pkg-config --cflags mariadb`
LDLIBS=`pkg-config --libs mariadb`
project:=bulletin
name:= index.cgi
sources:= index.c
objects:= $(sources:.c=.o)
prefix:=/var/www/$(project)
bindir:=$(prefix)
htaccess:= .htaccess
install_bin:= install
install_data:= install -m 644

all: $(name) $(htaccess)

$(name): $(objects)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

install: all
	$(install_bin) $(name) $(bindir)/$(name)
	$(install_data) $(htaccess) $(bindir)/$(htaccess)
	chcon -t httpd_sys_script_exec_t $(bindir)/$(name)

clean:
	rm -f $(name) $(objects)
