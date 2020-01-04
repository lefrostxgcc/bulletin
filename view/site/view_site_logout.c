#include <stdio.h>
#include "view_site.h"
#include "../read_replace_write.h"

void render_site_logout(int user_id)
{
  const struct Key_value map[] =
    {
     (const struct Key_value){.key = NULL, .value = NULL}
    };
  char buf[64];
  FILE *fp = fopen("site_index_logout.html", "r");
  printf("Set-Cookie: UserId=%d; path=/;"
	 " expires=Thu, 01 Jan 1970 00:00:00 GMT", user_id);
  printf("%s", "Content-Type: text/html\n\n");
  read_replace_write(fp, buf, sizeof(buf), map);
  printf("\n\n");
  fclose(fp);
}
