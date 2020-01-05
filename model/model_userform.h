#ifndef MODEL_USERFORM_H
#define MODEL_USERFORM_H

enum Userform_status
  {
   USERFORM_VALID,
   EMPTY_USERFORM_USERNAME = 1,
   EMPTY_USERFORM_PASSWORD = 1 << 1,
   EMPTY_USERFORM_CONFIRM_PASSWORD = 1 << 2,
   EMPTY_USERFORM_SURNAME = 1 << 3,
   EMPTY_USERFORM_NAME = 1 << 4,
   EMPTY_USERFORM_MIDDLENAME = 1 << 5,
   MISMATCH_USERFORM_PASSWORD_CONFIRM = 1 << 6
  };

enum Userform_element_index
  {
   USERFORM_USERNAME_INDEX,
   USERFORM_PASSWORD_INDEX,
   USERFORM_CONFIRM_PASSWORD_INDEX,
   USERFORM_SURNAME_INDEX,
   USERFORM_NAME_INDEX,
   USERFORM_MIDDLENAME_INDEX,
   USERFORM_ELEMENT_COUNT
  };

struct Model_userform
{
  char username[256];
  char password[256];
  char confirm_password[256];
  char surname[256];
  char name[256];
  char middlename[256];
};

int model_userform_validate(const struct Model_userform *userform);

const char **model_userform_attribute_labels(void);

#endif
