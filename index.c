#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "controller/controller_user.h"
#include "controller/controller_site.h"

int main(void)
{
  const char *request_uri = getenv("REQUEST_URI");
  printf("%s", "Content-Type: text/html\n\n");
  printf("%s", "<!DOCTYPE html><html>");
  printf("%s", "<head>");
  printf("%s", "<link rel=\"stylesheet\" href=\"/styles.css\">");
  printf("%s", "</head><body>");
  printf("%s", "<header><nav class=\"top-menu\">");
  printf("%s", "<ul class=\"menu-main\">");
  printf("%s", "<li class=\"left-item\"><a href=\"/\">Доска объявлений</a></li>");
  printf("%s", "<li class=\"right-item\"><a href=\"/site/login\">Вход</a></li>");
  printf("%s", "<li class=\"right-item\"><a href=\"/user/index\">Информация о пользователе</a></li>");

  printf("%s", "</ul></nav></header>");
  if (strcmp(request_uri, "/site/login") == 0)
    controller_site_action(request_uri);
  else if (strcmp(request_uri, "/user/index") == 0)
    controller_user_action(request_uri);
  else
    controller_site_action(request_uri);
  printf("</body></html>");
  printf("\n\n");
}
