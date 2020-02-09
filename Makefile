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
js_files:= $(wildcard js/*.js)
favicon_file:= icons/favicon.ico
data_files:= $(htmlt_files) $(css_files) $(js_files) $(image_files)
objects:= $(sources:.c=.o)
deps:= $(sources:.c=.d)
prefix:=/var/www/$(project)
bindir:=$(prefix)
htmltdir:=$(prefix)/htmlt
imagedir:=$(prefix)/images
jsdir:=$(prefix)/js
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
	-mkdir $(jsdir)
	$(install_data) $(js_files) $(jsdir)
	-mkdir -m 777 $(imagedir)
	chcon -t httpd_sys_rw_content_t $(imagedir)
	$(install_data) $(image_files) $(imagedir)
	$(install_data) $(favicon_file) $(bindir)

clean:
	rm -f $(name) $(objects)

uninstall:
	rm -rf $(bindir)/*

include $(deps)
