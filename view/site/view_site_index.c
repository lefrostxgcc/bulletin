#include <stdio.h>
#include <string.h>
#include "view_site.h"
#include "../read_replace_write.h"

void render_site_index(const char *username)
{
  const struct Key_value map[] =
    {
     (const struct Key_value){.key = "LOGIN", .value = username},
     (const struct Key_value){.key = "CONTENT", .value = "<h2>Главная</h2>"},
     (const struct Key_value){.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/site_index.html", map, NULL);
}

void render_site_index_guest(void)
{
  const struct Key_value map[] =
    {
     (const struct Key_value){.key = "CONTENT", .value = "<h2>Главная</h2>"},
     (const struct Key_value){.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/site_index_guest.html", map, NULL);
}
