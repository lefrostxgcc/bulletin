#include <stdio.h>
#include <string.h>
#include <time.h>
#include "view_site.h"
#include "../read_replace_write.h"

void render_site_login(void)
{
  const struct Key_value map[] =
    {
     (const struct Key_value){.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/site_login.html", map, NULL);
}

void render_site_login_fail(const char *username)
{
  const struct Key_value map[] =
    {
     (const struct Key_value){.key = "USERNAME", .value = username},
     (const struct Key_value){.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/site_login_fail.html", map, NULL);
}

void render_site_welcome(int user_id, int remember)
{
  const struct Key_value map[] =
    {
     (const struct Key_value){.key = NULL, .value = NULL}
    };
  char cookie_header[128] = "";
  if (remember)
    {
      time_t tomorrow = time(NULL) + 24 * 60 * 60;
      char time_buf[64] = "";
      strftime(time_buf, sizeof time_buf / sizeof time_buf[0],
	       "%a, %d %b %Y %H:%M:%S GMT", gmtime(&tomorrow));
      
      snprintf(cookie_header,
	       sizeof(cookie_header) / (sizeof(cookie_header[0])),
	       "Set-Cookie: UserId=%d; path=/; expires='%s'\n",
	       user_id, time_buf);
    }
  else
    {
      snprintf(cookie_header,
	       sizeof(cookie_header) / (sizeof(cookie_header[0])),
	       "Set-Cookie: UserId=%d; path=/\n",
	       user_id);
    }
  read_replace_write("htmlt/site_login_success.html", map, cookie_header);
}
