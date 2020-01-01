#include <string.h>
#include "controller_user.h"
#include "../view/user/view_user.h"

static void controller_user_action_index(void)
{
  render_user_index();
}

void controller_user_action(const char *request_uri)
{
  if (strcmp(request_uri, "/user/index") == 0)
    controller_user_action_index();
}
