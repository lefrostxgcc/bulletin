#include <string.h>
#include <time.h>
#include "view_site.h"
#include "../../model/model_bulletins.h"
#include "../read_replace_write.h"
#include "../../config/params.h"

void render_site_view_bulletin(const char *username,
			       const struct Model_bulletins *bulletin)
{
  char price_buf[256] = {'\0'};
  snprintf(price_buf, sizeof(price_buf) / sizeof(price_buf[0]),
	   "%.2f", bulletin->price);
  char avatar_buf[512] = {'\0'};
  char curr_year_buf[8] = {'\0'};
  time_t now = time(NULL);
  strftime(curr_year_buf, sizeof(curr_year_buf) / sizeof(curr_year_buf[0]),
	   "%Y", localtime(&now));
  if (strlen(bulletin->link) > 0)
    {
      strcat(avatar_buf, "/");
      strcat(avatar_buf, bulletin->link);
    }
  else
    {
      snprintf(avatar_buf, sizeof(avatar_buf)/(sizeof(avatar_buf[0])),
	       "%s%s", IMAGE_PATH, DEFAULT_IMAGE);
    }
  const struct Key_value map[] =
    {
     { .key = "LOGIN", .value = username },
     { .key = "BULLETIN_TITLE", .value = bulletin->title },
     { .key = "BULLETIN_AVATAR", .value = avatar_buf },
     { .key = "BULLETIN_INFO", .value = bulletin->info },
     { .key = "BULLETIN_PRICE", .value = price_buf },
     { .key = "BULLETIN_CITY", .value = bulletin->city },
     { .key = "BULLETIN_CONTACTS", .value = bulletin->contacts },
     { .key = "BULLETIN_DATE_PUB", .value = bulletin->date_pub },
     { .key = "CURRENT_YEAR", .value = curr_year_buf },
     { .key = NULL, .value = NULL }
    };
  read_replace_write("htmlt/site_view_bulletin.html", map, NULL);
}

void render_site_view_bulletin_guest(const struct Model_bulletins *bulletin)
{
  char price_buf[256] = {'\0'};
  snprintf(price_buf, sizeof(price_buf) / sizeof(price_buf[0]),
	   "%.2f", bulletin->price);
  char avatar_buf[512] = {'\0'};
  if (strlen(bulletin->link) > 0)
    {
      strcat(avatar_buf, "/");
      strcat(avatar_buf, bulletin->link);
    }
  else
    {
      snprintf(avatar_buf, sizeof(avatar_buf)/(sizeof(avatar_buf[0])),
	       "%s%s", IMAGE_PATH, DEFAULT_IMAGE);
    }
  const struct Key_value map[] =
    {
     { .key = "BULLETIN_TITLE", .value = bulletin->title },
     { .key = "BULLETIN_AVATAR", .value = avatar_buf },
     { .key = "BULLETIN_INFO", .value = bulletin->info },
     { .key = "BULLETIN_PRICE", .value = price_buf },
     { .key = "BULLETIN_CITY", .value = bulletin->city },
     { .key = "BULLETIN_CONTACTS", .value = bulletin->contacts },
     { .key = "BULLETIN_DATE_PUB", .value = bulletin->date_pub },
     { .key = NULL, .value = NULL }
    };
  read_replace_write("htmlt/site_view_bulletin_guest.html", map, NULL);
}
