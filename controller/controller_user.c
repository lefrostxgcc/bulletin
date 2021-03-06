#include <string.h>
#include "controller_user.h"
#include "session.h"
#include "../model/model_user.h"
#include "../model/model_userinfo.h"
#include "../view/user/view_user.h"
#include "../view/site/view_site.h"
#include "../model/model_userform.h"

static inline void controller_user_action_index(void)
{
  const int user_id = session_get_curr_user_id();
  struct Model_user *user =
    model_user_select_by_id(user_id);
  struct Model_userinfo *userinfo =
    model_userinfo_select_by_user_id(user_id);
  render_user_index(user, userinfo);
  model_user_free(user);
  model_userinfo_free(userinfo);
}

static void controller_user_action_add(void)
{
  struct Model_userform userform;
  if (model_userform_load_post(&userform))
    {
      if (model_userform_validate(&userform) == USERFORM_VALID)
	{
	  struct Model_user user = {'\0'};
	  strcpy(user.username, userform.username);
	  strcpy(user.password, userform.password);
	  model_user_save(&user);
	  struct Model_userinfo userinfo = {'\0'};
	  userinfo.user_id = model_user_find_user_id(userform.username,
						     userform.password);
	  strcpy(userinfo.surname, userform.surname);
	  strcpy(userinfo.name, userform.name);
	  strcpy(userinfo.middlename, userform.middlename);
	  model_userinfo_save(&userinfo);
	  session_redirect("/site/login", NULL);
	  return;
	}
    }
  render_user_add();
}

void controller_user_action(const char *request_uri)
{
  if (strcmp(request_uri, "/user/index") == 0)
    controller_user_action_index();
  else if (strcmp(request_uri, "/user/add") == 0)
    controller_user_action_add();
}
