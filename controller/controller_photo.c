#include <string.h>
#include "controller_photo.h"
#include "session.h"
#include "../model/model_user.h"
#include "../view/photo/view_photo.h"

static void controller_photo_action_index(void)
{
  const int user_id = session_get_curr_user_id();
  if (user_id > 0)
    {
      struct Model_user *user = model_user_select_by_id(user_id);
      if (user)
	render_photo_index(user->username);
      else
	session_redirect("/", NULL);
      model_user_free(user);
    }
  else
    {
      session_redirect("/site/login", NULL);
    }
}

void controller_photo_action(const char *request_uri)
{
  if (strstr(request_uri, "/photo/index") == request_uri)
    controller_photo_action_index();
  else
    session_redirect("/", NULL);
}
