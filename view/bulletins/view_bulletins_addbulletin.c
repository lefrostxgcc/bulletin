#include <stddef.h>
#include "view_bulletins.h"
#include "../read_replace_write.h"

void render_bulletins_addbulletin(const char *username)
{
  const struct Key_value map[] =
    {
     {.key = "LOGIN", .value = username},
     {.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/bulletins_addbulletin.html", map, NULL);
}
