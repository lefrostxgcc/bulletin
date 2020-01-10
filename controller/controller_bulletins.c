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

void controller_bulletins_action(const char *request_uri)
{
  (void) request_uri;
  controller_bulletins_action_index();
}
