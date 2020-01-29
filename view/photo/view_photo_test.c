#include <stddef.h>
#include "view_photo.h"
#include "../read_replace_write.h"

static void render_photo_test_user(const char *username)
{
  const struct Key_value map[] =
    {
     {.key = "LOGIN", .value = username},
     {.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/photo_test.html", map, NULL);
}

static void render_photo_test_guest(void)
{
  const struct Key_value map[] =
    {
     {.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/photo_test_guest.html", map, NULL);
}

void render_photo_test(const char *username)
{
  if (username)
    render_photo_test_user(username);
  else
    render_photo_test_guest();
}
