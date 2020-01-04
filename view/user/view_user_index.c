#include <stdio.h>
#include "view_user.h"
#include "../read_replace_write.h"
#include "../../model/model_user.h"
#include "../../model/model_userinfo.h"

static inline void render_user_index_guest(void)
{
  const struct Key_value map[] =
    {
     (const struct Key_value){.key = "LOGIN_HREF", .value = "/site/login"},
     (const struct Key_value){.key = "LOGIN", .value = "Вход"},
     (const struct Key_value){.key = "USERNAME", ""},
     (const struct Key_value){.key = "SURNAME", ""},
     (const struct Key_value){.key = NULL, .value = NULL}
    };
  read_replace_write("user_index.html", map, NULL);
}

static inline void render_user_index_user(const struct Model_user *user,
					  const struct Model_userinfo *userinfo)
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
     (const struct Key_value){.key = "USERNAME", .value = user->username},
     (const struct Key_value){.key = "SURNAME", .value = userinfo->surname},
     (const struct Key_value){.key = NULL, .value = NULL}
    };
  read_replace_write("user_index.html", map, NULL);
}

void render_user_index(const struct Model_user *user,
		       const struct Model_userinfo *userinfo)
{
  if (user && userinfo)
    render_user_index_user(user, userinfo);
  else
    render_user_index_guest();
}
