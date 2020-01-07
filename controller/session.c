#include <stdio.h>
#include <stdlib.h>
#include "session.h"
#include "../view/read_replace_write.h"

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

void session_redirect(const char *url)
{
  const struct Key_value map[] =
    {
     {.key = "REDIRECT_HREF", .value = url},
     {.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/redirect.html", map, NULL);
}

static char unescape_char(const char *s)
{
  char digit = (*s >= 'A') ? *s - 'A' + 10 : *s - '0';
  digit *= 16;
  ++s;
  digit += (*s >= 'A') ? *s - 'A' + 10 : *s - '0';
  return digit;
}

void unescape_url(char *url)
{
  char *decoded_url = url;
  while (*url)
    {
      if (*url == '%')
	{
	  *decoded_url = unescape_char(++url);
	  ++url;
	}
      else if (*url == '+')
	*decoded_url = ' ';
      else
	*decoded_url = *url;
      ++url;
      ++decoded_url;
    }
  *decoded_url = '\0';
}
