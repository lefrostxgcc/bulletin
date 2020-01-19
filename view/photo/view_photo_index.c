#include <stddef.h>
#include "view_photo.h"
#include "../read_replace_write.h"

void render_photo_index(const char *username)
{
  const struct Key_value map[] =
    {
     {.key = "LOGIN", .value = username},
     {.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/photo_index.html", map, NULL);
}
