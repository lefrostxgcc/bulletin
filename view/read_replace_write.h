#ifndef READ_REPLACE_WRITE_H
#define READ_REPLACE_WRITE_H

#include <stdio.h>

void read_replace_write(FILE *f,
		       char *buf,
		       size_t buf_size,
		       void (*cb_replace_func)(const char *, int)
		       );

#endif
