#include <stdio.h>
#include "view_site.h"

static void show_header()
{
  printf("%s", "Content-Type: text/html\n\n");
  printf("%s", "<!DOCTYPE html><html>");
  printf("%s", "<head>");
  printf("%s", "<link rel=\"stylesheet\" href=\"/styles.css\">");
  printf("%s", "</head><body>");
  printf("%s", "<header><nav class=\"top-menu\">");
  printf("%s", "<ul class=\"menu-main\">");
  printf("%s", "<li class=\"left-item\"><a href=\"/\">Доска объявлений</a></li>");
  printf("%s", "<li class=\"right-item\"><a href=\"/site/login\">Вход</a></li>");
  printf("%s", "<li class=\"right-item\"><a href=\"/user/index\">Информация о пользователе</a></li>");
  printf("%s", "</ul></nav></header>");
}

static void show_footer()
{
  printf("</body></html>");
  printf("\n\n");
}

void render_site_login(void)
{
  show_header();
  printf("%s",
	 "<form action=\"/site/login\" method=\"post\">"
	 "<table><tr>"
	 "<td><label>Login:</label></td>"
	 "<td><input name=\"login\" size=\"15\"></td>"
	 "</tr><tr>"
	 "<td><label>Password:</label></td>"
	 "<td><input name=\"password\" size=\"15\"></td>"
	 "</tr><tr>"
	 "<td><input type=\"submit\" value=\"Login\"></td></tr>"
	 "</table>"
	 "</form>"
	 );
  show_footer();
}

void render_site_login_fail(const char *username)
{
  show_header();
  printf("%s",
	 "<form action=\"/site/login\" method=\"post\">"
	 "<table><tr>"
	 "<td><label>Login:</label></td>"
	 "<td><input name=\"login\" size=\"15\"");
  printf(" value=\"%s\"", username);
  printf("%s", "></td>"
	 "</tr><tr>"
	 "<td><label>Password:</label></td>"
	 "<td><input name=\"password\" size=\"15\"></td>"
	 "</tr><tr>"
	 "<td><input type=\"submit\" value=\"Login\"></td></tr>"
	 "</table>"
	 "</form>"
	 );
  printf("%s", "Ошибка! Неверный логин или пароль.");
  show_footer();
}

static void show_header_index()
{
  printf("%s", "Set-Cookie: UserName: chip\n");
  printf("%s", "Content-Type: text/html\n\n");
  printf("%s", "<!DOCTYPE html><html>");
  printf("%s", "<head>");
  printf("%s", "<meta http-equiv=\"Refresh\" content=\"0; url=/site/index\" />");
  printf("%s", "</head><body>");
}

void render_site_welcome(const char *username)
{
  (void) username;
  show_header_index();
  show_footer();
}
