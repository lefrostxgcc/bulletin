#ifndef READ_REPLACE_WRITE_H
#define READ_REPLACE_WRITE_H

#include <stdio.h>

struct Key_value
{
  const char *key;
  const char *value;
};

const char *find_value_by_key(const char *key, const struct Key_value map[]);

void read_replace_write(FILE *f,
			char *buf,
			size_t buf_size,
			const struct Key_value map[],
			void (*cb_replace_func)(const char *,
						const struct Key_value map[],
						int status)
			);

#endif
