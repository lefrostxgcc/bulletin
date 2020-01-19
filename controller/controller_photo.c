#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "controller_photo.h"
#include "session.h"
#include "../model/model_user.h"
#include "../model/model_photo.h"
#include "../view/photo/view_photo.h"

static int get_photo_id_from_query_string(void)
{
  const char *query_string = getenv("QUERY_STRING");
  int id = 0;
  if (!query_string)
    return 0;
  if (sscanf(query_string, "id=%d", &id) != 1)
    return 0;
  return id;
}

static void controller_photo_action_index(void)
{
  const int user_id = session_get_curr_user_id();
  if (user_id > 0)
    {
      struct Model_user *user = model_user_select_by_id(user_id);
      if (user)
	{
	  const int bull_id = get_photo_id_from_query_string();
	  struct Model_photo *photos = select_photos_by_bull_id(bull_id);
	  render_photo_index(user->username, photos);
	  free(photos);
	}
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
