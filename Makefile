.PHONY: all clean install install_bin install_data install_config \
	uninstall

CFLAGS=-Wall -Wextra -Werror `pkg-config --cflags mariadb`
LDLIBS=`pkg-config --libs mariadb` -lcrypto
project:=bulletin
name:= index.cgi
sources:= $(wildcard *.c controller/*.c model/*.c view/*.c \
	view/site/*.c view/user/*.c view/bulletins/*.c \
	view/photo/*.c)
image_files:= $(wildcard images/*.png)
htmlt_files:= $(wildcard htmlt/*.html)
css_files:= $(wildcard css/*.css)
data_files:= $(htmlt_files) $(css_files)
objects:= $(sources:.c=.o)
deps:= $(sources:.c=.d)
prefix:=/var/www/$(project)
bindir:=$(prefix)
htmltdir:=$(prefix)/htmlt
imagedir:=$(prefix)/images
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

install: install_bin install_config install_data

install_bin: all
	$(install_bin) $(name) $(bindir)
	chcon -t httpd_sys_script_exec_t $(bindir)/$(name)

install_config: $(htaccess)
	$(install_data) $(htaccess) $(bindir)

install_data: $(data_files)
	-mkdir $(htmltdir)
	$(install_data) $(htmlt_files) $(htmltdir)
	-mkdir $(cssdir)
	$(install_data) $(css_files) $(cssdir)
	-mkdir $(imagedir)
	$(install_data) $(image_files) $(imagedir)

clean:
	rm -f $(name) $(objects)

uninstall:
	rm -rf $(bindir)/*

include $(deps)
