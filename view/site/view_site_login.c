#include <stdio.h>
#include "view_site.h"
#include "../read_replace_write.h"

void render_site_login(void)
{
  const struct Key_value map[] =
    {
     (const struct Key_value){.key = NULL, .value = NULL}
    };
  read_replace_write("site_login.html", map, NULL);
}

void render_site_login_fail(const char *username)
{
  const struct Key_value map[] =
    {
     (const struct Key_value){.key = "USERNAME", .value = username},
     (const struct Key_value){.key = NULL, .value = NULL}
    };
  read_replace_write("site_login_fail.html", map, NULL);
}

void render_site_welcome(int user_id)
{
  const struct Key_value map[] =
    {
     (const struct Key_value){.key = NULL, .value = NULL}
    };
  char cookie_header[64];
  snprintf(cookie_header,
	   sizeof(cookie_header) / (sizeof(cookie_header[0])),
	   "Set-Cookie: UserId=%d; path=/\n",
	   user_id);
  read_replace_write("site_login_success.html", map, cookie_header);
}
