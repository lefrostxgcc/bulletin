#include <stdio.h>
#include "view_user.h"
#include "../read_replace_write.h"
#include "../../model/model_user.h"
#include "../../model/model_userform.h"

void render_user_add(const struct Model_user *user)
{
  const char **labels = model_userform_attribute_labels();
  const char *login_caption = "Вход";
  const char *login_href = "/site/login";
  char buf[320];
  if (user)
    {
      snprintf(buf,
	       sizeof(buf) / sizeof(buf[0]),
	       "Выход(%s)",
	       user->username
	       );
      login_caption = buf;
      login_href = "/site/logout";
    }
  const struct Key_value map[] =
    {
     {.key = "LOGIN_HREF", .value = login_href},
     {.key = "LOGIN", .value = login_caption},
     {.key = "USERFORM_LOGIN_LABEL", .value = labels[USERFORM_USERNAME_INDEX]},
     {.key = "USERFORM_PASSWORD_LABEL", .value = "Пароль"},
     {.key = "USERFORM_CONFIRM_PASSWORD_LABEL", .value = "Подтвердить пароль"},
     {.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/user_add.html", map, NULL);
}
