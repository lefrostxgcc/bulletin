#include <stdio.h>
#include <string.h>
#include "view_site.h"
#include "../read_replace_write.h"

static inline void render_site_index_as_guest(void)
{
  const struct Key_value map[] =
    {
     (const struct Key_value){.key = "LOGIN_HREF", .value = "/site/login"},
     (const struct Key_value){.key = "LOGIN", .value = "Вход"},
     (const struct Key_value){.key = "CONTENT", .value = "<h2>Главная</h2>"},
     (const struct Key_value){.key = NULL, .value = NULL}
    };
  read_replace_write("site_index.html", map, NULL);
}

static inline void render_site_index_as_user(const char *username)
{
  char login_caption[320];
  snprintf(login_caption,
	   sizeof(login_caption) / sizeof(login_caption[0]),
	   "Выход(%s)",
	   username
	   );
  const struct Key_value map[] =
    {
     (const struct Key_value){.key = "LOGIN_HREF", .value = "/site/logout"},
     (const struct Key_value){.key = "LOGIN", .value = login_caption},
     (const struct Key_value){.key = "CONTENT", .value = "<h2>Главная</h2>"},
     (const struct Key_value){.key = NULL, .value = NULL}
    };
  read_replace_write("site_index.html", map, NULL);
}

void render_site_index(const char *username)
{
  if (username)
    render_site_index_as_user(username);
  else
    render_site_index_as_guest();
}
