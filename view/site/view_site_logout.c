#include <stdio.h>
#include "view_site.h"
#include "../read_replace_write.h"

void render_site_logout(int user_id)
{
  const struct Key_value map[] =
    {
     (const struct Key_value){.key = NULL, .value = NULL}
    };
  char cookie_header[128];
  snprintf(cookie_header,
	   sizeof(cookie_header) / (sizeof(cookie_header[0])),
	   "Set-Cookie: UserId=%d; path=/;"
	   " expires=Thu, 01 Jan 1970 00:00:00 GMT\n",
	   user_id);
  read_replace_write("htmlt/site_index_logout.html", map, cookie_header);
}
