#include <stddef.h>
#include "view_user.h"
#include "../read_replace_write.h"
#include "../../model/model_userform.h"

void render_user_add(void)
{
  const char **labels = model_userform_attribute_labels();
  const struct Key_value map[] =
    {
     {
      .key = "USERFORM_LOGIN_LABEL",
      .value = labels[USERFORM_USERNAME_INDEX]
     },
     {
      .key = "USERFORM_PASSWORD_LABEL",
      .value = labels[USERFORM_PASSWORD_INDEX]
     },
     {
      .key = "USERFORM_CONFIRM_PASSWORD_LABEL",
      .value = labels[USERFORM_CONFIRM_PASSWORD_INDEX]
     },
     {
      .key = "USERFORM_SURNAME_LABEL",
      .value = labels[USERFORM_SURNAME_INDEX]
     },
     {
      .key = "USERFORM_NAME_LABEL",
      .value = labels[USERFORM_NAME_INDEX]
     },
     {
      .key = "USERFORM_MIDDLENAME_LABEL",
      .value = labels[USERFORM_MIDDLENAME_INDEX]
     },
     {.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/user_add.html", map, NULL);
}
