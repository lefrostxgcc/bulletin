#include <string.h>
#include <stdlib.h>
#include "view_site.h"
#include "../../model/model_bulletins.h"
#include "../../model/model_photo.h"
#include "../read_replace_write.h"
#include "../../config/params.h"
#include "../curr_date.h"

struct Photo_link_info
{
  char link[256];
  char info[256];
};

static struct Photo_link_info *
alloc_photo_row(const struct Model_photo model[])
{
  if (!model)
    return NULL;
  const struct Model_photo *p = model;
  int count = 0;
  while (p->id != 0)
    {
      ++p;
      ++count;
    }
  struct Photo_link_info *row =
    calloc(count + 1, sizeof(struct Photo_link_info));
  for (int i = 0; i < count; i++)
    {
      strcpy(row[i].link, model[i].link);
      strcpy(row[i].info, model[i].info);
    }
  return row;
}

static void free_photo_row(struct Photo_link_info *row)
{
  free(row);
}

static void print_photo_row(const char *filename, void *embed)
{
  if (!filename || !embed)
    return;
  FILE *f = fopen(filename, "r");
  if (!f)
    return;
  struct Photo_link_info *row = (struct Photo_link_info *) embed;
  while (strlen(row->link) > 0)
    {
      const struct Key_value map[] =
	{
	 {.key = "PHOTO_LINK", .value = row->link},
	 {.key = "PHOTO_INFO", .value = row->info},
	 {.key = NULL, .value = NULL}
	};
      read_replace_write_embed(f, map);
      rewind(f);
      ++row;
    }
  fclose(f);
}

void render_site_view_bulletin(const char *username,
			       const struct Model_bulletins *bulletin,
			       const struct Model_photo photos[])
{
  char price_buf[256] = {'\0'};
  snprintf(price_buf, sizeof(price_buf) / sizeof(price_buf[0]),
	   "%.2f", bulletin->price);
  char avatar_buf[512] = {'\0'};
  char curr_year[8] = {'\0'};
  get_curr_year(curr_year, sizeof(curr_year) / sizeof(curr_year[0]));
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
  struct Photo_link_info *embed = alloc_photo_row(photos);
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
     { .key = "CURRENT_YEAR", .value = curr_year },
     {
      .key = "BULLETIN_PHOTOS_EMBED",
      .value = "htmlt/site_view_bulletin_embed.html",
      .embed = embed,
      .cb_print_embed = print_photo_row
     },
     { .key = NULL, .value = NULL }
    };
  read_replace_write("htmlt/site_view_bulletin.html", map, NULL);
  free_photo_row(embed);
}

void render_site_view_bulletin_guest(const struct Model_bulletins *bulletin,
				     const struct Model_photo photos[])
{
  char price_buf[256] = {'\0'};
  snprintf(price_buf, sizeof(price_buf) / sizeof(price_buf[0]),
	   "%.2f", bulletin->price);
  char avatar_buf[512] = {'\0'};
  char curr_year[8] = {'\0'};
  get_curr_year(curr_year, sizeof(curr_year) / sizeof(curr_year[0]));
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
  struct Photo_link_info *embed = alloc_photo_row(photos);
  const struct Key_value map[] =
    {
     { .key = "BULLETIN_TITLE", .value = bulletin->title },
     { .key = "BULLETIN_AVATAR", .value = avatar_buf },
     { .key = "BULLETIN_INFO", .value = bulletin->info },
     { .key = "BULLETIN_PRICE", .value = price_buf },
     { .key = "BULLETIN_CITY", .value = bulletin->city },
     { .key = "BULLETIN_CONTACTS", .value = bulletin->contacts },
     { .key = "BULLETIN_DATE_PUB", .value = bulletin->date_pub },
     { .key = "CURRENT_YEAR", .value = curr_year },
     {
      .key = "BULLETIN_PHOTOS_EMBED",
      .value = "htmlt/site_view_bulletin_embed.html",
      .embed = embed,
      .cb_print_embed = print_photo_row
     },
     { .key = NULL, .value = NULL }
    };
  read_replace_write("htmlt/site_view_bulletin_guest.html", map, NULL);
  free_photo_row(embed);
}
