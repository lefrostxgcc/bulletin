#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "view_bulletins.h"
#include "../read_replace_write.h"

struct Bulletins_wait_row
{
  char id[256];
  char title[256];
};

static struct Bulletins_wait_row *
alloc_wait_rows(const struct Model_bulletins model[])
{
  const struct Model_bulletins *p = model;
  int row_count = 0;
  while (p->id != 0)
    {
      ++p;
      ++row_count;
    }
  struct Bulletins_wait_row *rows =
    calloc(row_count + 1, sizeof(struct Bulletins_wait_row));
  for (int i = 0; i < row_count; i++)
    {
      snprintf(rows[i].id, sizeof(rows[i].id)/(sizeof(rows[i].id[0])),
	       "%d", model[i].id);
      strcpy(rows[i].title, model[i].title);
    }
  return rows;
}

void free_wait_rows(struct Bulletins_wait_row *rows)
{
  free(rows);
}

void render_bulletins_index(const char *username)
{
  const struct Key_value map[] =
    {
     {.key = "LOGIN", .value = username},
     {.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/bulletins_index.html", map, NULL);
}

void render_bulletins_index_public(const char *username)
{
  const struct Key_value map[] =
    {
     {.key = "LOGIN", .value = username},
     {.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/bulletins_index_public.html", map, NULL);
}

void print_wait_rows(const char *filename, void *embed)
{
  struct Bulletins_wait_row *rows = (struct Bulletins_wait_row *) embed;
  FILE *f = fopen(filename, "r");
  if (!f)
    return;
  while (strlen(rows->id) > 0)
    {
      const struct Key_value map[] =
	{
	 {.key = "BULLETINS_WAIT_ID", .value = rows->id},
	 {.key = "BULLETINS_WAIT_TITLE", .value = rows->title},
	 {.key = NULL, .value = NULL}
	};
      read_replace_write_embed(f, map);
      rewind(f);
      ++rows;
    }
  fclose(f);
}

void render_bulletins_index_wait(const char *username,
				 const struct Model_bulletins bulletins[])
{
  struct Bulletins_wait_row *embed = alloc_wait_rows(bulletins);
  const struct Key_value map[] =
    {
     {.key = "LOGIN", .value = username},
     {
      .key = "BULLETINS_WAIT_ROWS",
      .value = "htmlt/bulletins_index_wait_embed.html",
      .embed = embed,
      .cb_print_embed = print_wait_rows
     },
     {.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/bulletins_index_wait.html", map, NULL);
  free_wait_rows(embed);
}

void render_bulletins_index_deleted(const char *username)
{
  const struct Key_value map[] =
    {
     {.key = "LOGIN", .value = username},
     {.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/bulletins_index_deleted.html", map, NULL);
}
