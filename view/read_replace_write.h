#ifndef READ_REPLACE_WRITE_H
#define READ_REPLACE_WRITE_H

#include <stdio.h>

typedef void (*print_embed_t)(const char *filename, void *embed);

struct Key_value
{
  const char *key;
  const char *value;
  void *embed;
  print_embed_t cb_print_embed;
};

void read_replace_write(const char *filename,
			const struct Key_value map[],
			const char *http_headers);

void read_replace_write_embed(FILE *f, const struct Key_value map[]);

#endif
