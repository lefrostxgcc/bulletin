#include <stddef.h>
#include "view_user.h"
#include "../read_replace_write.h"
#include "../../model/model_user.h"
#include "../../model/model_userinfo.h"
#include "../curr_date.h"

void render_user_index(const struct Model_user *user,
		       const struct Model_userinfo *userinfo)
{
  char curr_year[8] = {'\0'};
  get_curr_year(curr_year, sizeof(curr_year) / sizeof(curr_year[0]));
  const struct Key_value map[] =
    {
     (const struct Key_value){.key = "LOGIN", .value = user->username},
     (const struct Key_value){.key = "USERNAME", .value = user->username},
     (const struct Key_value){.key = "SURNAME", .value = userinfo->surname},
     { .key = "CURRENT_YEAR", .value = curr_year },
     (const struct Key_value){.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/user_index.html", map, NULL);
}
