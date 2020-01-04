#include <stdio.h>
#include <string.h>
#include "read_replace_write.h"

const char *find_value_by_key(const char *key, const struct Key_value map[])
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

void read_replace_write(FILE *f,
			char *buf,
			size_t buf_size,
			const struct Key_value map[],
			void (*cb_replace_func)(const char *,
						const struct Key_value map[],
						int status)
			)
{
  if (!f || !buf || buf_size == 0 || !map || !cb_replace_func)
    return;
  size_t i = 0;
  int c = EOF;
  enum state {OUT, IN_WORD} state = OUT;
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
	      cb_replace_func(buf, map, 1);
	      i = 0;
	      state = OUT;
	    }
	  else
	    {
	      buf[i++] = c;
	      if (i + 1 >= buf_size)
		{
		  buf[i] = '\0';
		  cb_replace_func(buf, map, 0);
		  i = 0;
		  state = OUT;
		}
	    }
	  break;
	}
    }
}
