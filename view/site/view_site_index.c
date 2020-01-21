#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "view_site.h"
#include "../../model/model_bulletins.h"
#include "../read_replace_write.h"
#include "../../config/params.h"

struct Bulletins_info
{
  char title[256];
  char price[256];
  char city[256];
};

static struct Bulletins_info *
alloc_info_rows(const struct Model_bulletins model[])
{
  const struct Model_bulletins *p = model;
  int row_count = 0;
  while (p->id != 0)
    {
      ++p;
      ++row_count;
    }
  struct Bulletins_info *rows =
    calloc(row_count + 1, sizeof(struct Bulletins_info));
  for (int i = 0; i < row_count; i++)
    {
      strcpy(rows[i].title, model[i].title);
      snprintf(rows[i].price, sizeof(rows[i].price)/(sizeof(rows[i].price[0])),
	       "%.2f", model[i].price);
      strcpy(rows[i].city, model[i].city);
    }
  return rows;
}

void free_info_rows(struct Bulletins_info *rows)
{
  free(rows);
}

void print_info_rows(const char *filename, void *embed)
{
  if (!filename || !embed)
    return;
  FILE *f = fopen(filename, "r");
  if (!f)
    return;
  struct Bulletins_info *rows = (struct Bulletins_info *) embed;
  while (strlen(rows->title) > 0)
    {
      const struct Key_value map[] =
	{
	 {.key = "IMAGE_PATH", .value = IMAGE_PATH},
	 {.key = "DEFAULT_IMAGE", .value = DEFAULT_IMAGE},
	 {.key = "BULLETIN_TITLE", .value = rows->title},
	 {.key = "BULLETIN_PRICE", .value = rows->price},
	 {.key = "BULLETIN_CITY", .value = rows->city},
	 {.key = NULL, .value = NULL}
	};
      read_replace_write_embed(f, map);
      rewind(f);
      ++rows;
    }
  fclose(f);
}

void render_site_index(const char *username,
		       const struct Model_bulletins *bulletins)
{
  struct Bulletins_info *embed = alloc_info_rows(bulletins);
  const struct Key_value map[] =
    {
     {.key = "LOGIN", .value = username},
     {
      .key = "BULLETINS_PUBLIC_EMBED",
      .value = "htmlt/site_index_embed.html",
      .embed = embed,
      .cb_print_embed = print_info_rows
     },
     {.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/site_index.html", map, NULL);
  free_info_rows(embed);
}

void render_site_index_guest(const struct Model_bulletins *bulletins)
{
  struct Bulletins_info *embed = alloc_info_rows(bulletins);
  const struct Key_value map[] =
    {
     {
      .key = "BULLETINS_PUBLIC_EMBED",
      .value = "htmlt/site_index_embed.html",
      .embed = embed,
      .cb_print_embed = print_info_rows
     },
     {.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/site_index_guest.html", map, NULL);
  free_info_rows(embed);
}
