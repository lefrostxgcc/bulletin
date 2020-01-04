#include <stdio.h>
#include <string.h>
#include "view_site.h"
#include "../read_replace_write.h"
/*
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
*/
void replace_func(const char *placeholder,
		  const struct Key_value map[],
		  int status)
{
  const char *value = NULL;
  if (status != 1)
    printf("%s", placeholder);
  else if ((value = find_value_by_key(placeholder, map)))
    printf("%s", value);
  else
    printf("<p>|%s|</p>", placeholder);
}

void render_site_index(const char *username)
{
  const struct Key_value guest_map[] =
    {
     (const struct Key_value){.key = "BODY", .value = "<h2>Главная</h2>"},
     (const struct Key_value){.key = NULL, .value = NULL}
    };
  const struct Key_value user_map[] =
    {
     (const struct Key_value){.key = "LOGIN", .value = username},
     (const struct Key_value){.key = "BODY", .value = "<h2>Главная</h2>"},
     (const struct Key_value){.key = NULL, .value = NULL}
    };
  FILE *fp = NULL;
  const struct Key_value *map = NULL;
  if (!username)
    {
      fp = fopen("site_index_guest.html", "r");
      map = guest_map;
    }
  else
    {
      fp = fopen("site_index_user.html", "r");
      map = user_map;
    }
  printf("%s", "Content-Type: text/html\n\n");
  char buf[64];
  read_replace_write(fp, buf, sizeof(buf), map, replace_func);
  printf("\n\n");
  fclose(fp);
}
