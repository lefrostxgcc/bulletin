#include <stdio.h>
#include "view_site.h"

void render_site_login(void)
{
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
}

void render_site_login_fail(const char *username)
{
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
}

void render_site_welcome(const char *username)
{
  printf("%s %s %s", "<div><h2> Привет", username, "!</h2></div>");
}
