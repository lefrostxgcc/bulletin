#ifndef READ_REPLACE_WRITE_H
#define READ_REPLACE_WRITE_H

#include <stdio.h>

struct Key_value
{
  const char *key;
  const char *value;
};

void read_replace_write(FILE *f,
			char *buf,
			size_t buf_size,
			const struct Key_value map[]
			);

#endif
