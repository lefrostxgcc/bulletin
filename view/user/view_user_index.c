#include <stdio.h>
#include "view_user.h"
#include "../../model/model_user.h"
#include "../../model/model_userinfo.h"

void
render_user_index(struct Model_user *user, struct Model_userinfo *userinfo)
{
  printf("<h2>Информация о пользователе</h2>");
  printf("<div>");
  printf("<p>Логин <strong>%s</strong></p>", user->username);
  printf("<p>Фамилия <strong>%s</strong></p>", userinfo->surname);
  printf("</div>");
}
