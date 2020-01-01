.PHONY: all clean install

CFLAGS=-Wall -Wextra `pkg-config --cflags mariadb`
LDLIBS=`pkg-config --libs mariadb` -lcrypto
project:=bulletin
name:= index.cgi
sources:= index.c view/user/view_user_index.c controller/controller_user.c
objects:= $(sources:.c=.o)
prefix:=/var/www/$(project)
bindir:=$(prefix)
htaccess:= .htaccess
css_file:=styles.css
install_bin:= install
install_data:= install -m 644

all: $(name) $(htaccess)

$(name): $(objects)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

index.o: controller/controller_user.h
view/user/view_user_index.o: view/user/view_user.h
controller/controller_user.o: view/user/view_user.h \
	controller/controller_user.h

install: all
	$(install_bin) $(name) $(bindir)/$(name)
	$(install_data) $(htaccess) $(bindir)/$(htaccess)
	$(install_data) $(css_file) $(bindir)/$(css_file)
	chcon -t httpd_sys_script_exec_t $(bindir)/$(name)

clean:
	rm -f $(name) $(objects)
