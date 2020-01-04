#include <stdio.h>
#include "view_user.h"
#include "../read_replace_write.h"
#include "../../model/model_user.h"

static inline void render_user_add_as_guest(void)
{
  const struct Key_value map[] =
    {
     (const struct Key_value){.key = "LOGIN_HREF", .value = "/site/login"},
     (const struct Key_value){.key = "LOGIN", .value = "Вход"},
     (const struct Key_value){.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/user_add.html", map, NULL);
}

static inline void render_user_add_as_user(const struct Model_user *user)
{
  char login_caption[320];
  snprintf(login_caption,
	   sizeof(login_caption) / sizeof(login_caption[0]),
	   "Выход(%s)",
	   user->username
	   );
  const struct Key_value map[] =
    {
     (const struct Key_value){.key = "LOGIN_HREF", .value = "/site/logout"},
     (const struct Key_value){.key = "LOGIN", .value = login_caption},
     (const struct Key_value){.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/user_add.html", map, NULL);
}

void render_user_add(const struct Model_user *user)
{
  if (user)
    render_user_add_as_user(user);
  else
    render_user_add_as_guest();
}
