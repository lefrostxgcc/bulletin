#include <time.h>
#include "curr_date.h"

void get_curr_year(char buf[], size_t size)
{
  if (!buf)
    return;
  time_t now = time(NULL);
  strftime(buf, size, "%Y", localtime(&now));
}
