#include <stdio.h>
#include <string.h>
#include "read_replace_write.h"

static const char *find_value_by_key(const char *key,
				     const struct Key_value map[])
{
  if (!key || !map)
    return NULL;
  while (map->key)
    {
      if (strcmp(key, map->key) == 0)
	return map->value;
      ++map;
    }
  return NULL;
}

static void replace_func(const char *placeholder,
			 const struct Key_value map[],
			 int status)
{
  const char *value = NULL;
  if (status != 1)
    printf("%s", placeholder);
  else if ((value = find_value_by_key(placeholder, map)))
    printf("%s", value);
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
