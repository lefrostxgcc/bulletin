#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "controller/controller_user.h"
#include "controller/controller_site.h"

int main(void)
{
  const char *request_uri = getenv("REQUEST_URI");
  if (strcmp(request_uri, "/site/login") == 0)
    controller_site_action(request_uri);
  else if (strcmp(request_uri, "/site/logout") == 0)
    controller_site_action(request_uri);
  else if (strcmp(request_uri, "/user/index") == 0)
    controller_user_action(request_uri);
  else if (strcmp(request_uri, "/user/add") == 0)
    controller_user_action(request_uri);
  else
    controller_site_action(request_uri);
}
