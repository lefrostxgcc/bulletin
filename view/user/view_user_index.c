#include <stdio.h>
#include "view_user.h"
#include "../../model/model_user.h"
#include "../../model/model_userinfo.h"

static void show_header()
{
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
}

static void show_footer()
{
  printf("</body></html>");
  printf("\n\n");
}

void
render_user_index(struct Model_user *user, struct Model_userinfo *userinfo)
{
  show_header();
  printf("<h2>Информация о пользователе</h2>");
  printf("<div>");
  printf("<p>Логин <strong>%s</strong></p>", user->username);
  printf("<p>Фамилия <strong>%s</strong></p>", userinfo->surname);
  printf("</div>");
  show_footer();
}
