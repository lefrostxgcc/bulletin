#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "view_bulletins.h"
#include "../read_replace_write.h"
#include "../curr_date.h"

struct Bulletins_wait_row
{
  char id[256];
  char title[256];
};

struct Bulletins_public_row
{
  char id[256];
  char title[256];
};

struct Bulletins_delete_row
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

static struct Bulletins_public_row *
alloc_public_rows(const struct Model_bulletins model[])
{
  const struct Model_bulletins *p = model;
  int row_count = 0;
  while (p->id != 0)
    {
      ++p;
      ++row_count;
    }
  struct Bulletins_public_row *rows =
    calloc(row_count + 1, sizeof(struct Bulletins_public_row));
  for (int i = 0; i < row_count; i++)
    {
      snprintf(rows[i].id, sizeof(rows[i].id)/(sizeof(rows[i].id[0])),
	       "%d", model[i].id);
      strcpy(rows[i].title, model[i].title);
    }
  return rows;
}

static struct Bulletins_delete_row *
alloc_delete_rows(const struct Model_bulletins model[])
{
  const struct Model_bulletins *p = model;
  int row_count = 0;
  while (p->id != 0)
    {
      ++p;
      ++row_count;
    }
  struct Bulletins_delete_row *rows =
    calloc(row_count + 1, sizeof(struct Bulletins_delete_row));
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

void free_public_rows(struct Bulletins_public_row *rows)
{
  free(rows);
}

void free_delete_rows(struct Bulletins_delete_row *rows)
{
  free(rows);
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

void print_public_rows(const char *filename, void *embed)
{
  struct Bulletins_public_row *rows = (struct Bulletins_public_row *) embed;
  FILE *f = fopen(filename, "r");
  if (!f)
    return;
  while (strlen(rows->id) > 0)
    {
      const struct Key_value map[] =
	{
	 {.key = "BULLETINS_PUBLIC_ID", .value = rows->id},
	 {.key = "BULLETINS_PUBLIC_TITLE", .value = rows->title},
	 {.key = NULL, .value = NULL}
	};
      read_replace_write_embed(f, map);
      rewind(f);
      ++rows;
    }
  fclose(f);
}

void print_delete_rows(const char *filename, void *embed)
{
  struct Bulletins_delete_row *rows = (struct Bulletins_delete_row *) embed;
  FILE *f = fopen(filename, "r");
  if (!f)
    return;
  while (strlen(rows->id) > 0)
    {
      const struct Key_value map[] =
	{
	 {.key = "BULLETINS_DELETE_ID", .value = rows->id},
	 {.key = "BULLETINS_DELETE_TITLE", .value = rows->title},
	 {.key = NULL, .value = NULL}
	};
      read_replace_write_embed(f, map);
      rewind(f);
      ++rows;
    }
  fclose(f);
}

void render_bulletins_index(const char *username,
			    const struct Model_bulletins bulletins[])
{
  render_bulletins_index_wait(username, bulletins);
}

void render_bulletins_index_wait(const char *username,
				 const struct Model_bulletins bulletins[])
{
  struct Bulletins_wait_row *embed = alloc_wait_rows(bulletins);
  char curr_year[8] = {'\0'};
  get_curr_year(curr_year, sizeof(curr_year) / sizeof(curr_year[0]));
  const struct Key_value map[] =
    {
     {.key = "LOGIN", .value = username},
     {
      .key = "BULLETINS_WAIT_ROWS",
      .value = "htmlt/bulletins_index_wait_embed.html",
      .embed = embed,
      .cb_print_embed = print_wait_rows
     },
     { .key = "CURRENT_YEAR", .value = curr_year },
     {.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/bulletins_index_wait.html", map, NULL);
  free_wait_rows(embed);
}

void render_bulletins_index_public(const char *username,
				   const struct Model_bulletins bulletins[])
{
  struct Bulletins_public_row *embed = alloc_public_rows(bulletins);
  char curr_year[8] = {'\0'};
  get_curr_year(curr_year, sizeof(curr_year) / sizeof(curr_year[0]));
  const struct Key_value map[] =
    {
     {.key = "LOGIN", .value = username},
     {
      .key = "BULLETINS_PUBLIC_ROWS",
      .value = "htmlt/bulletins_index_public_embed.html",
      .embed = embed,
      .cb_print_embed = print_public_rows
     },
     { .key = "CURRENT_YEAR", .value = curr_year },
     {.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/bulletins_index_public.html", map, NULL);
  free_public_rows(embed);
}

void render_bulletins_index_deleted(const char *username,
				    const struct Model_bulletins bulletins[])
{
  struct Bulletins_delete_row *embed = alloc_delete_rows(bulletins);
  char curr_year[8] = {'\0'};
  get_curr_year(curr_year, sizeof(curr_year) / sizeof(curr_year[0]));
  const struct Key_value map[] =
    {
     {.key = "LOGIN", .value = username},
     {
      .key = "BULLETINS_DELETE_ROWS",
      .value = "htmlt/bulletins_index_deleted_embed.html",
      .embed = embed,
      .cb_print_embed = print_delete_rows
     },
     { .key = "CURRENT_YEAR", .value = curr_year },
     {.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/bulletins_index_deleted.html", map, NULL);
  free_delete_rows(embed);
}
