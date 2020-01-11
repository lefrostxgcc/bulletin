#include <string.h>
#include "controller_bulletins.h"
#include "session.h"
#include "../model/model_user.h"
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

void controller_bulletins_action(const char *request_uri)
{
  if (strcmp(request_uri, "/bulletins/index") == 0)
    controller_bulletins_action_index();
  else if (strcmp(request_uri, "/bulletins/index/public") == 0)
    controller_bulletins_action_index_public();
  else if (strcmp(request_uri, "/bulletins/index/wait") == 0)
    controller_bulletins_action_index_wait();
  else if (strcmp(request_uri, "/bulletins/index/deleted") == 0)
    controller_bulletins_action_index_deleted();
  else
    session_redirect("/bulletins/index", NULL);
}
