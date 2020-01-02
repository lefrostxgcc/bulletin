#include <stdio.h>
#include "view_user.h"
#include "../../model/model_user.h"

void render_user_index(struct Model_user *user)
{
  printf("<h2>Информация о пользователе</h2>");
  printf("<div>");
  printf("<p>Логин <strong>%s</strong></p>", user->username);
  printf("<p>Пароль <strong>%s</strong></p>", user->password);
  printf("</div>");
}
