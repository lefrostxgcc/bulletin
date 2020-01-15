#include <stdio.h>
#include "view_bulletins.h"
#include "../read_replace_write.h"

struct Bulletins_wait_row
{
  const char *id;
  const char *title;
};

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
  while (rows->id)
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

void render_bulletins_index_wait(const char *username)
{
  struct Bulletins_wait_row embed[] =
    {
     {.id = "1", .title = "Продается домик"},
     {.id = "2", .title = "Продается коляска"},
     {.id = NULL, .title = NULL}
    };
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
