#include <stddef.h>
#include "view_site.h"
#include "../../model/model_bulletins.h"
#include "../read_replace_write.h"

void render_site_view_bulletin(const char *username,
			       const struct Model_bulletins *bulletin)
{
  const struct Key_value map[] =
    {
     { .key = "LOGIN", .value = username },
     { .key = "BULLETIN_TITLE", .value = bulletin->title },
     { .key = "BULLETIN_INFO", .value = bulletin->info },
     { .key = NULL, .value = NULL }
    };
  read_replace_write("htmlt/site_view_bulletin.html", map, NULL);
}

void render_site_view_bulletin_guest(const struct Model_bulletins *bulletin)
{
  const struct Key_value map[] =
    {
     { .key = "BULLETIN_TITLE", .value = bulletin->title, },
     { .key = "BULLETIN_INFO", .value = bulletin->info },
     { .key = NULL, .value = NULL }
    };
  read_replace_write("htmlt/site_view_bulletin_guest.html", map, NULL);
}
