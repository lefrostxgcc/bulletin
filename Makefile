.PHONY: all clean install

CFLAGS=-Wall -Wextra `pkg-config --cflags mariadb`
LDLIBS=`pkg-config --libs mariadb` -lcrypto
project:=bulletin
name:= index.cgi
sources:= index.c view/user/view_user_index.c controller/controller_user.c \
model/model_user.c model/model_userinfo.c controller/controller_site.c \
view/site/view_site_login.c view/site/view_site_index.c \
view/site/view_site_logout.c controller/session.c \
view/read_replace_write.c view/user/view_user_add.c
htmlt_files:= $(wildcard htmlt/*.html)
css_files:= $(wildcard css/*.css)
objects:= $(sources:.c=.o)
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

index.o: controller/controller_user.h
view/user/view_user_index.o: view/user/view_user.h model/model_user.h \
view/read_replace_write.h
controller/controller_user.o: view/user/view_user.h \
	controller/controller_user.h model/model_user.h \
	model/model_userinfo.h controller/session.h
model/model_user.o: model/model_user.h model/model_db.h
model/model_userinfo.o: model/model_userinfo.h model/model_db.h
controller/controller_site.o: view/site/view_site.h \
	controller/controller_site.h model/model_user.h \
	controller/session.h
view/site/view_site_login.o: view/site/view_site.h view/read_replace_write.h
view/site/view_site_index.o: view/site/view_site.h view/read_replace_write.h
view/site/view_site_logout.o: view/site/view_site.h view/read_replace_write.h
controller/session.o: controller/session.h
view/read_replace_write.o: view/read_replace_write.h
view/user/view_user_add.o: view/user/view_user.h view/read_replace_write.h \
model/model_user.h

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
