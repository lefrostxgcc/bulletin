#include <stdio.h>
#include <string.h>
#include "view_site.h"
#include "../read_replace_write.h"

static void show_header_old(const char *username)
{
  printf("%s", "Content-Type: text/html\n\n");
  printf("%s", "<!DOCTYPE html><html>");
  printf("%s", "<head>");
  printf("%s", "<link rel=\"stylesheet\" href=\"/styles.css\">");
  printf("%s", "</head><body>");
  printf("%s", "<header><nav class=\"top-menu\">");
  printf("%s", "<ul class=\"menu-main\">");
  printf("%s", "<li class=\"left-item\"><a href=\"/\">Доска объявлений</a></li>");
  if (username)
    printf("<li class=\"right-item\"><a href=\"/site/logout\">Выход(%s)</a></li>", username);
  else
    printf("%s", "<li class=\"right-item\"><a href=\"/site/login\">Вход</a></li>");
  printf("%s", "<li class=\"right-item\"><a href=\"/user/index\">Информация о пользователе</a></li>");
  printf("%s", "</ul></nav></header>");
}

static void show_footer_old(void)
{
  printf("</body></html>");
  printf("\n\n");
}

void replace_func(const char *placeholder, int status)
{
  (void) status;
  if (strcmp(placeholder, "BODY") == 0)
    printf("%s", "This is index page");
  else
    printf("<p>|%s|</p>", placeholder);
}

void render_site_index(const char *username)
{
  if (username)
    {
      show_header_old(username);
      printf("%s", "<h2>Главная страница</h2>");
      show_footer_old();
      return;
    }
  printf("%s", "Content-Type: text/html\n\n");
  FILE *fp = fopen("site_index_guest.html", "r");
  char buf[64];
  read_replace_write(fp, buf, sizeof(buf)/sizeof(buf[0]), replace_func);
  printf("\n\n");
}
