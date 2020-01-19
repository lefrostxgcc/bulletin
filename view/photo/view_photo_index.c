#include <stdlib.h>
#include <string.h>
#include "view_photo.h"
#include "../../model/model_photo.h"
#include "../read_replace_write.h"

struct Photo_front
{
  char link[256];
  char info[256];
};

static struct Photo_front *
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
  struct Photo_front *row = calloc(count + 1, sizeof(struct Photo_front));
  for (int i = 0; i < count; i++)
    {
      strcpy(row[i].link, model[i].link);
      strcpy(row[i].info, model[i].info);
    }
  return row;
}

static void free_photo_row(struct Photo_front *row)
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
  struct Photo_front *row = (struct Photo_front *) embed;
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

void render_photo_index(const char *username,
			const struct Model_photo photos[])
{
  struct Photo_front *embed = alloc_photo_row(photos);
  const struct Key_value map[] =
    {
     {.key = "LOGIN", .value = username},
     {
      .key = "PHOTO_EMBED",
      .value = "htmlt/photo_index_embed.html",
      .embed = embed,
      .cb_print_embed = print_photo_row
     },
     {.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/photo_index.html", map, NULL);
  free_photo_row(embed);
}
