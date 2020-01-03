#include <stdio.h>
#include <stdlib.h>
#include "session.h"

int session_get_curr_user_id(void)
{
  const char *cookie = getenv("HTTP_COOKIE");
  if (!cookie)
    return 0;
  int user_id = 0;
  if(sscanf(cookie, "UserId=%d", &user_id) != 1)
    return 0;
  if (user_id < 0)
    user_id = 0;
  return user_id;
}
