#include <string.h>
#include "model_userform.h"

int model_userform_validate(const struct Model_userform *userform)
{
  int status = USERFORM_VALID;
  if (strlen(userform->username) == 0)
    status |= EMPTY_USERFORM_USERNAME;
  if (strlen(userform->password) == 0)
    status |= EMPTY_USERFORM_PASSWORD;
  if (strlen(userform->confirm_password) == 0)
    status |= EMPTY_USERFORM_CONFIRM_PASSWORD;
  if (strlen(userform->surname) == 0)
    status |= EMPTY_USERFORM_SURNAME;
  if (strlen(userform->name) == 0)
    status |= EMPTY_USERFORM_NAME;
  if (strlen(userform->middlename) == 0)
    status |= EMPTY_USERFORM_MIDDLENAME;
  if (strcmp(userform->password, userform->confirm_password) != 0)
    status |= MISMATCH_USERFORM_PASSWORD_CONFIRM;
  return status;
}

const char **model_userform_attribute_labels(void)
{
  static const char *labels[USERFORM_ELEMENT_COUNT] =
    {
     [USERFORM_USERNAME_INDEX] = "Login",
    };
  return labels;
}
