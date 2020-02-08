#include <stddef.h>
#include "view_photo.h"
#include "../read_replace_write.h"
#include "../curr_date.h"

static void render_photo_test_user(const char *username)
{
  char curr_year[8] = {'\0'};
  get_curr_year(curr_year, sizeof(curr_year) / sizeof(curr_year[0]));
  const struct Key_value map[] =
    {
     {.key = "LOGIN", .value = username},
     { .key = "CURRENT_YEAR", .value = curr_year },
     {.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/photo_test.html", map, NULL);
}

static void render_photo_test_guest(void)
{
  char curr_year[8] = {'\0'};
  get_curr_year(curr_year, sizeof(curr_year) / sizeof(curr_year[0]));
  const struct Key_value map[] =
    {
     { .key = "CURRENT_YEAR", .value = curr_year },
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
