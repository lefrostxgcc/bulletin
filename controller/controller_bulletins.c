#include <string.h>
#include "controller_bulletins.h"
#include "session.h"
#include "../model/model_user.h"
#include "../model/model_bulletins.h"
#include "../model/model_bulletinsform.h"
#include "../view/bulletins/view_bulletins.h"

static void controller_bulletins_action_index(void)
{
  const int user_id = session_get_curr_user_id();
  struct Model_user *user = model_user_select_by_id(user_id);
  render_bulletins_index(user->username);
  model_user_free(user);
}

static void controller_bulletins_action_index_public(void)
{
  const int user_id = session_get_curr_user_id();
  struct Model_user *user = model_user_select_by_id(user_id);
  render_bulletins_index_public(user->username);
  model_user_free(user);
}

static void controller_bulletins_action_index_wait(void)
{
  const int user_id = session_get_curr_user_id();
  struct Model_user *user = model_user_select_by_id(user_id);
  render_bulletins_index_wait(user->username);
  model_user_free(user);
}

static void controller_bulletins_action_index_deleted(void)
{
  const int user_id = session_get_curr_user_id();
  struct Model_user *user = model_user_select_by_id(user_id);
  render_bulletins_index_deleted(user->username);
  model_user_free(user);
}

static void controller_bulletins_action_addbulletin(void)
{
  const int session_user_id = session_get_curr_user_id();
  struct Model_bulletinsform form;
  if (model_bulletinsform_load_by_post_request(&form))
    {
      if (model_bulletinsform_validate(&form) == BULLETINSFORM_VALID)
	{
	  struct Model_bulletins bulletin;
	  model_bulletins_set_new(&bulletin, &form, session_user_id);
	  model_bulletins_save(&bulletin);
	  session_redirect("/bulletins/index", NULL);
	  return;
	}
    }
  struct Model_user *user = model_user_select_by_id(session_user_id);
  render_bulletins_addbulletin(user->username);
  model_user_free(user);
}

void controller_bulletins_action(const char *request_uri)
{
  if(session_get_curr_user_id() == 0)
    session_redirect("/site/login", NULL);
  else if (strcmp(request_uri, "/bulletins/index") == 0)
    controller_bulletins_action_index();
  else if (strcmp(request_uri, "/bulletins/index/public") == 0)
    controller_bulletins_action_index_public();
  else if (strcmp(request_uri, "/bulletins/index/wait") == 0)
    controller_bulletins_action_index_wait();
  else if (strcmp(request_uri, "/bulletins/index/deleted") == 0)
    controller_bulletins_action_index_deleted();
  else if (strcmp(request_uri, "/bulletins/addbulletin") == 0)
    controller_bulletins_action_addbulletin();
  else
    session_redirect("/bulletins/index", NULL);
}
