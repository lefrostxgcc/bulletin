#ifndef READ_REPLACE_WRITE_H
#define READ_REPLACE_WRITE_H

struct Key_value
{
  const char *key;
  const char *value;
};

void read_replace_write(const char *filename,
			const struct Key_value map[],
			const char *http_headers);

#endif
