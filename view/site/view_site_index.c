#include <stdio.h>
#include <string.h>
#include "view_site.h"

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

int read_placeholder(FILE *f, char *buf, size_t buf_size)
{
  size_t i = 0;
  int c = EOF;
  while ((c = fgetc(f)) != EOF)
    {
      if (c != '}')
	  buf[i] = c;
      else
	{
	  buf[i] = '\0';
	  return 1;
	}
      if (++i >= buf_size)
	break;
    }
  buf[i] = '\0';
  return 0;
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
  int c = EOF;
  char placeholder[64];
  while ((c = fgetc(fp)) != EOF)
    {
      if (c != '{')
	putchar(c);
      else
	{
	  read_placeholder(fp, placeholder, sizeof(placeholder));
	  if (strcmp(placeholder, "BODY") == 0)
	    printf("%s", "This is index page");
	  else
	    printf("<p>|%s|</p>", placeholder);
	}
    }
  printf("\n\n");
}
