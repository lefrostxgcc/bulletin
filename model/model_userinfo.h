#ifndef MODEL_USERINFO_H
#define MODEL_USERINFO_H

struct Model_userinfo
{
  int id;
  int user_id;
  char surname[256];
  char name[256];
  char middlename[256];
};

struct Model_userinfo* model_userinfo_select_by_user_id(int user_id);
void model_userinfo_free(struct Model_userinfo *userinfo);

#endif
