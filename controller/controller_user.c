#include <string.h>
#include "controller_user.h"
#include "../model/model_user.h"
#include "../view/user/view_user.h"

static void controller_user_action_index(void)
{
  struct Model_user *user = model_user_select_by_id(3);
  render_user_index(user);
  model_user_free(user);
}

void controller_user_action(const char *request_uri)
{
  if (strcmp(request_uri, "/user/index") == 0)
    controller_user_action_index();
}
