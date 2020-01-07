#ifndef MODEL_USER_H
#define MODEL_USER_H

struct Model_user
{
  int id;
  char username[256];
  char password[256];
  char auth_key[256];
  char access_token[256];
};

struct Model_user* model_user_select_by_id(int id);
void model_user_free(struct Model_user *model);
int model_user_find_user_id(const char *username,
			    const char *password);
int model_user_save(const struct Model_user *user);

#endif
