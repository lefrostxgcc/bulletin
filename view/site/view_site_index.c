#include <stdio.h>
#include <string.h>
#include "view_site.h"
#include "../read_replace_write.h"

void render_site_index_guest(void)
{
    const struct Key_value map[] =
    {
     (const struct Key_value){.key = "BODY", .value = "<h2>Главная</h2>"},
     (const struct Key_value){.key = NULL, .value = NULL}
    };
  char buf[64];
  FILE *fp = fopen("site_index_guest.html", "r");
  printf("%s", "Content-Type: text/html\n\n");
  read_replace_write(fp, buf, sizeof(buf), map);
  printf("\n\n");
  fclose(fp);
}

void render_site_index_user(const char *username)
{
  const struct Key_value map[] =
    {
     (const struct Key_value){.key = "LOGIN", .value = username},
     (const struct Key_value){.key = "BODY", .value = "<h2>Главная</h2>"},
     (const struct Key_value){.key = NULL, .value = NULL}
    };
  char buf[64];
  FILE *fp = fopen("site_index_user.html", "r");
  printf("%s", "Content-Type: text/html\n\n");
  read_replace_write(fp, buf, sizeof(buf), map);
  printf("\n\n");
  fclose(fp);
}

void render_site_index(const char *username)
{
  if (username)
    render_site_index_user(username);
  else
    render_site_index_guest();
}
