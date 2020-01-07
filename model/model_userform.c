#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../controller/session.h"
#include "model_userform.h"

#define MAX_CONTENT_LEN 1600
#define MAX_FIELD_LEN 255

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
     [USERFORM_USERNAME_INDEX] = "Логин",
     [USERFORM_PASSWORD_INDEX] = "Пароль",
     [USERFORM_CONFIRM_PASSWORD_INDEX] = "Подтвердить пароль",
     [USERFORM_SURNAME_INDEX] = "Фамилия",
     [USERFORM_NAME_INDEX] = "Имя",
     [USERFORM_MIDDLENAME_INDEX] = "Отчество",
    };
  return labels;
}

int model_userform_load_post(struct Model_userform *userform)
{
  const char *content_length = getenv("CONTENT_LENGTH");
  if (content_length == NULL)
      return 0;
  char content[MAX_CONTENT_LEN + 1] = {'\0'};
  int length = atoi(content_length);
  fgets(content, length + 1, stdin);
  unescape_url(content);
  memset(userform, '\0', sizeof(struct Model_userform));
  sscanf(content,
	 "login=%255[^&]&password=%255[^&]&confirm_password=%255[^&]"
	 "&surname=%255[^&]&name=%255[^&]&middlename=%255[^&]",
	 userform->username, userform->password,
	 userform->confirm_password, userform->surname,
	 userform->name, userform->middlename);
  return 1;
}
