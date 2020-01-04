#include <stdio.h>
#include <string.h>
#include "view_site.h"
#include "../read_replace_write.h"

static inline void render_site_index_guest(void)
{
  const struct Key_value map[] =
    {
     (const struct Key_value){.key = "BODY", .value = "<h2>Главная</h2>"},
     (const struct Key_value){.key = NULL, .value = NULL}
    };
  read_replace_write("site_index_guest.html", map, NULL);
}

static inline void render_site_index_user(const char *username)
{
  const struct Key_value map[] =
    {
     (const struct Key_value){.key = "LOGIN", .value = username},
     (const struct Key_value){.key = "BODY", .value = "<h2>Главная</h2>"},
     (const struct Key_value){.key = NULL, .value = NULL}
    };
  read_replace_write("site_index_user.html", map, NULL);
}

void render_site_index(const char *username)
{
  if (username)
    render_site_index_user(username);
  else
    render_site_index_guest();
}
