#include <stdio.h>
#include "view_site.h"
#include "../read_replace_write.h"

void render_site_login(void)
{
  const struct Key_value map[] =
    {
     (const struct Key_value){.key = NULL, .value = NULL}
    };
  char buf[64];
  FILE *fp = fopen("site_login.html", "r");
  printf("%s", "Content-Type: text/html\n\n");
  read_replace_write(fp, buf, sizeof(buf), map);
  printf("\n\n");
  fclose(fp);
}

void render_site_login_fail(const char *username)
{
  const struct Key_value map[] =
    {
     (const struct Key_value){.key = "USERNAME", .value = username},
     (const struct Key_value){.key = NULL, .value = NULL}
    };
  char buf[64];
  FILE *fp = fopen("site_login_fail.html", "r");
  printf("%s", "Content-Type: text/html\n\n");
  read_replace_write(fp, buf, sizeof(buf), map);
  printf("\n\n");
  fclose(fp);
}
void render_site_welcome(int user_id)
{
  const struct Key_value map[] =
    {
     (const struct Key_value){.key = NULL, .value = NULL}
    };
  char buf[64];
  FILE *fp = fopen("site_login_success.html", "r");
  printf("Set-Cookie: UserId=%d; Path=/\n", user_id);
  printf("%s", "Content-Type: text/html\n\n");
  read_replace_write(fp, buf, sizeof(buf), map);
  printf("\n\n");
  fclose(fp);
}
