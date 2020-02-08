#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "view_site.h"
#include "../../model/model_bulletins.h"
#include "../read_replace_write.h"
#include "../../config/params.h"
#include "../curr_date.h"

struct Bulletins_info
{
  char id[256];
  char title[256];
  char price[256];
  char city[256];
  char link[256];
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
      snprintf(rows[i].id, sizeof(rows[i].id)/(sizeof(rows[i].id[0])),
	       "%d", model[i].id);
      strcpy(rows[i].title, model[i].title);
      snprintf(rows[i].price, sizeof(rows[i].price)/(sizeof(rows[i].price[0])),
	       "%.2f", model[i].price);
      strcpy(rows[i].city, model[i].city);
      if (strlen(model[i].link) > 0)
	{
	  strcat(rows[i].link, "/");
	  strcat(rows[i].link, model[i].link);
	}
      else
	{
	  snprintf(rows[i].link, sizeof(rows[i].link)/(sizeof(rows[i].link[0])),
		   "%s%s", IMAGE_PATH, DEFAULT_IMAGE);
	}

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
	 {.key = "BULLETIN_ID", .value = rows->id},
	 {.key = "BULLETIN_AVATAR", .value = rows->link},
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
  char curr_year[8] = {'\0'};
  get_curr_year(curr_year, sizeof(curr_year) / sizeof(curr_year[0]));
  const struct Key_value map[] =
    {
     {.key = "LOGIN", .value = username},
     {
      .key = "BULLETINS_PUBLIC_EMBED",
      .value = "htmlt/site_index_embed.html",
      .embed = embed,
      .cb_print_embed = print_info_rows
     },
     { .key = "CURRENT_YEAR", .value = curr_year },
     {.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/site_index.html", map, NULL);
  free_info_rows(embed);
}

void render_site_index_guest(const struct Model_bulletins *bulletins)
{
  struct Bulletins_info *embed = alloc_info_rows(bulletins);
  char curr_year[8] = {'\0'};
  get_curr_year(curr_year, sizeof(curr_year) / sizeof(curr_year[0]));
  const struct Key_value map[] =
    {
     {
      .key = "BULLETINS_PUBLIC_EMBED",
      .value = "htmlt/site_index_embed.html",
      .embed = embed,
      .cb_print_embed = print_info_rows
     },
     { .key = "CURRENT_YEAR", .value = curr_year },
     {.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/site_index_guest.html", map, NULL);
  free_info_rows(embed);
}
