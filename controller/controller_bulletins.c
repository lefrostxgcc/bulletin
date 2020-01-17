#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "controller_bulletins.h"
#include "session.h"
#include "../model/model_user.h"
#include "../model/model_bulletins.h"
#include "../model/model_bulletinsform.h"
#include "../view/bulletins/view_bulletins.h"

static int get_bulletin_id_from_query_string(void)
{
  const char *query_string = getenv("QUERY_STRING");
  int id = 0;
  if (!query_string)
    return 0;
  if (sscanf(query_string, "id=%d", &id) != 1)
    return 0;
  return id;
}

static void controller_bulletins_action_index(void)
{
  const int user_id = session_get_curr_user_id();
  struct Model_user *user = model_user_select_by_id(user_id);
  struct Model_bulletins *bulletins =
    select_bulletins_by_userid_and_status(user_id, "wait");
  render_bulletins_index(user->username, bulletins);
  free(bulletins);
  model_user_free(user);
}

static void controller_bulletins_action_index_public(void)
{
  const int user_id = session_get_curr_user_id();
  struct Model_user *user = model_user_select_by_id(user_id);
  struct Model_bulletins *bulletins =
    select_bulletins_by_userid_and_status(user_id, "public");
  render_bulletins_index_public(user->username, bulletins);
  free(bulletins);
  model_user_free(user);
}

static void controller_bulletins_action_index_wait(void)
{
  const int user_id = session_get_curr_user_id();
  struct Model_user *user = model_user_select_by_id(user_id);
  struct Model_bulletins *bulletins =
    select_bulletins_by_userid_and_status(user_id, "wait");
  render_bulletins_index_wait(user->username, bulletins);
  free(bulletins);
  model_user_free(user);
}

static void controller_bulletins_action_index_deleted(void)
{
  const int user_id = session_get_curr_user_id();
  struct Model_user *user = model_user_select_by_id(user_id);
  struct Model_bulletins *bulletins =
    select_bulletins_by_userid_and_status(user_id, "delete");
  render_bulletins_index_deleted(user->username, bulletins);
  free(bulletins);
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
	  model_bulletins_insert(&bulletin);
	  session_redirect("/bulletins/index", NULL);
	  return;
	}
    }
  struct Model_user *user = model_user_select_by_id(session_user_id);
  render_bulletins_addbulletin(user->username);
  model_user_free(user);
}

static void controller_bulletins_action_editbulletin(void)
{
  const int bulletin_id = get_bulletin_id_from_query_string();
  if (bulletin_id < 0)
    {
      session_redirect("/bulletins/index", NULL);
      return;
    }
  const int session_user_id = session_get_curr_user_id();
  struct Model_bulletinsform form;
  if (model_bulletinsform_load_by_post_request(&form))
    {
      if (model_bulletinsform_validate(&form) == BULLETINSFORM_VALID)
	{
	  struct Model_bulletins bulletin;
	  model_bulletins_set_new(&bulletin, &form, session_user_id);
	  bulletin.id = bulletin_id;
	  model_bulletins_edit(&bulletin);
	  session_redirect("/bulletins/index", NULL);
	  return;
	}
    }
  struct Model_bulletins *bulletin = select_bulletin_by_id(bulletin_id);
  if (!bulletin)
    {
      session_redirect("/bulletins/index", NULL);
      return;
    }
  model_bulletinsform_init_from_bulletin(&form, bulletin);
  struct Model_user *user = model_user_select_by_id(session_user_id);
  render_bulletins_editbulletin(user->username, &form, bulletin_id);
  model_user_free(user);
  model_bulletins_free(bulletin);
}

static void set_status(const char *status)
{
  int id = get_bulletin_id_from_query_string();
  if (id > 0)
    {
      struct Model_bulletins *bulletin = select_bulletin_by_id(id);
      if (bulletin)
	{
	  if (strcmp(status, "public") == 0)
	    model_bulletins_set_public(bulletin);
	  else if (strcmp(status, "delete") == 0)
	    model_bulletins_set_delete(bulletin);
	  else if (strcmp(status, "wait") == 0)
	    model_bulletins_set_wait(bulletin);
	  model_bulletins_update(bulletin);
	}
      model_bulletins_free(bulletin);
    }
  session_redirect("/bulletins/index", NULL);
}

static void controller_bulletins_action_public(void)
{
  set_status("public");
}

static void controller_bulletins_action_delete(void)
{
  set_status("delete");
}

static void controller_bulletins_action_wait(void)
{
  set_status("wait");
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
  else if (strstr(request_uri, "/bulletins/editbulletin") == request_uri)
    controller_bulletins_action_editbulletin();
  else if (strstr(request_uri, "/bulletins/public?id=") == request_uri)
    controller_bulletins_action_public();
  else if (strstr(request_uri, "/bulletins/wait?id=") == request_uri)
    controller_bulletins_action_wait();
  else if (strstr(request_uri, "/bulletins/delete?id=") == request_uri)
    controller_bulletins_action_delete();
  else
    session_redirect("/bulletins/index", NULL);
}
