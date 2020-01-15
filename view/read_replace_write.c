#include <stdio.h>
#include <string.h>
#include "read_replace_write.h"

static int find_record_by_key(const char *key,
			     const struct Key_value map[])
{
  if (!key || !map)
    return -1;
  int i = 0;
  while (map->key)
    {
      if (strcmp(key, map->key) == 0)
	return i;
      ++map;
      ++i;
    }
  return -1;
}

static void replace_func(const char *placeholder,
			 const struct Key_value map[],
			 int status)
{
  int i = 0;
  if (status != 1)
    printf("%s", placeholder);
  else if ((i = find_record_by_key(placeholder, map)) >= 0)
    {
      if (map[i].cb_print_embed == NULL)
	printf("%s", map[i].value);
      else
	map[i].cb_print_embed(map[i].value, map[i].embed);
    }
  else
    printf("%s", placeholder);
}

void read_replace_write(const char *filename,
			const struct Key_value map[],
			const char *http_headers)
{
  if (!filename || !map)
    return;
  FILE *f = fopen(filename, "r");
  char buf[64];
  const size_t buf_size = sizeof(buf) / sizeof(buf[0]);
  size_t i = 0;
  int c = EOF;
  enum state {OUT, IN_WORD} state = OUT;
  if (http_headers)
    printf("%s", http_headers);
  printf("%s", "Content-Type: text/html\n\n");
  while ((c = fgetc(f)) != EOF)
    {
      switch(state)
	{
	case OUT:
	  if (c == '{')
	    state = IN_WORD;
	  else
	    putchar(c);
	  break;
	case IN_WORD:
	  if (c == '}')
	    {
	      buf[i] = '\0';
	      replace_func(buf, map, 1);
	      i = 0;
	      state = OUT;
	    }
	  else
	    {
	      buf[i++] = c;
	      if (i + 1 >= buf_size)
		{
		  buf[i] = '\0';
		  replace_func(buf, map, 0);
		  i = 0;
		  state = OUT;
		}
	    }
	  break;
	}
    }
  printf("\n\n");
  fclose(f);
}
