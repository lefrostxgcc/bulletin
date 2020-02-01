#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "controller_photo.h"
#include "session.h"
#include "../model/model_user.h"
#include "../model/model_photo.h"
#include "../model/model_photoform.h"
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
	  render_photo_index(user->username, photos, bull_id);
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

static void controller_photo_action_add(void)
{
  struct Model_photoform *form = model_photoform_load_by_post_request();
  const int user_id = session_get_curr_user_id();
  if (user_id > 0)
    {
      struct Model_user *user = model_user_select_by_id(user_id);
      if (user)
	{
	  const int bull_id = get_photo_id_from_query_string();
	  if (form)
	    {
	      struct Model_photo photo;
	      model_photo_set_new(&photo, form, bull_id);
	      model_photo_insert(&photo);
	      char redirect_href[64] = {'\0'};
	      snprintf(redirect_href,
		       sizeof redirect_href / sizeof redirect_href[0],
		       "/photo/index?id=%d",
		       bull_id);
	      session_redirect(redirect_href, NULL);
	    }
	  else
	    {
	      render_photo_add(user->username, bull_id);
	    }
	}
      else
	session_redirect("/", NULL);
      model_user_free(user);
    }
  else
    {
      session_redirect("/site/login", NULL);
    }
  model_photoform_free(form);
}

static void controller_photo_action_test(void)
{
  const int user_id = session_get_curr_user_id();
  struct Model_user *user = model_user_select_by_id(user_id);
  render_photo_test(user ? user->username : NULL);
  model_user_free(user);
}

static void controller_photo_action_setinfo(void)
{
  struct Model_photo photo = {'\0'};
  if (model_photo_load_info_by_post(&photo))
    model_photo_update_info_by_id(&photo);
  printf("Content-Type: text/plain\n\n");
  printf("Запрос выполнен: id=%d info: %s\n", photo.id, photo.info);
  printf("\n\n");
}

static void controller_photo_action_getinfo(void)
{
  struct Model_photo photo = {'\0'};
  if (model_photo_load_id_by_post(&photo))
    select_model_photo_by_id(&photo, photo.id);
  printf("Content-Type: text/plain\n\n");
  printf("%s", photo.info);
  printf("\n\n");
}

void controller_photo_action(const char *request_uri)
{
  if (strstr(request_uri, "/photo/index") == request_uri)
    controller_photo_action_index();
  else if (strstr(request_uri, "/photo/add") == request_uri)
    controller_photo_action_add();
  else if (strstr(request_uri, "/photo/test") == request_uri)
    controller_photo_action_test();
  else if (strstr(request_uri, "/photo/setinfo") == request_uri)
    controller_photo_action_setinfo();
  else if (strstr(request_uri, "/photo/getinfo") == request_uri)
    controller_photo_action_getinfo();
  else
    session_redirect("/", NULL);
}
