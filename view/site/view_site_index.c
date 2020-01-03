#include <stdio.h>
#include <stdlib.h>
#include "view_site.h"

static void show_header(void)
{
  printf("%s", "Content-Type: text/html\n\n");
  printf("%s", "<!DOCTYPE html><html>");
  printf("%s", "<head>");
  printf("%s", "<link rel=\"stylesheet\" href=\"/styles.css\">");
  printf("%s", "</head><body>");
  printf("%s", "<header><nav class=\"top-menu\">");
  printf("%s", "<ul class=\"menu-main\">");
  printf("%s", "<li class=\"left-item\"><a href=\"/\">Доска объявлений</a></li>");
  const char *cookie = getenv("HTTP_COOKIE");
  if (!cookie)
    {
      printf("%s", "<li class=\"right-item\"><a href=\"/site/login\">Вход</a></li>");
    }
  else
    {
      char username[256] = {'\0'};
      sscanf(cookie, "UserName: %255s", username);
      if (username[0])
	{
	  printf("<li class=\"right-item\"><a href=\"/site/logout\">Выход(%s)</a></li>", username);
	}
      else
	{
	  printf("%s", "<li class=\"right-item\"><a href=\"/site/login\">Вход</a></li>");
	}
    }
  printf("%s", "<li class=\"right-item\"><a href=\"/user/index\">Информация о пользователе</a></li>");
  printf("%s", "</ul></nav></header>");
}

static void show_footer(void)
{
  printf("</body></html>");
  printf("\n\n");
}

void render_site_index(void)
{
  show_header();
  printf("%s", "<h2>Главная страница</h2>");
  show_footer();
}
