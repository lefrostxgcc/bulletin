#include <stdio.h>
#include <string.h>
#include "view_site.h"
#include "../read_replace_write.h"

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
  char buf[64];
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
  read_replace_write(fp, buf, sizeof(buf), map);
  printf("\n\n");
  fclose(fp);
}
