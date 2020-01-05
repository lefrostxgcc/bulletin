.PHONY: all clean install

CFLAGS=-Wall -Wextra `pkg-config --cflags mariadb`
LDLIBS=`pkg-config --libs mariadb` -lcrypto
project:=bulletin
name:= index.cgi
sources:= $(wildcard *.c controller/*.c model/*.c view/*.c \
	view/site/*.c view/user/*.c)
htmlt_files:= $(wildcard htmlt/*.html)
css_files:= $(wildcard css/*.css)
objects:= $(sources:.c=.o)
deps:= $(sources:.c=.d)
prefix:=/var/www/$(project)
bindir:=$(prefix)
htmltdir:=$(prefix)/htmlt
cssdir:=$(prefix)/css
htaccess:= .htaccess
install_bin:= install
install_data:= install -m 644

all: $(name)

$(name): $(objects)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

%.d : %.c
	@set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,.*o[ :],$*\.o $*\.d :,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

install: all
	-mkdir $(htmltdir)
	-mkdir $(cssdir)
	$(install_bin) $(name) $(bindir)/$(name)
	$(install_data) $(htaccess) $(bindir)
	$(install_data) $(htmlt_files) $(htmltdir)
	$(install_data) $(css_files) $(cssdir)
	chcon -t httpd_sys_script_exec_t $(bindir)/$(name)

clean:
	rm -f $(name) $(objects)

include $(deps)
