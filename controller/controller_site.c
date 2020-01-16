#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "session.h"
#include "controller_site.h"
#include "../model/model_user.h"
#include "../model/model_bulletins.h"
#include "../view/site/view_site.h"

#define MAX_USERNAME_LEN 15
#define MAX_PASSWORD_LEN 15
#define MAX_CONTENT_LEN 63

static void login_success(int user_id, int remember)
{
  char cookie_header[128] = "";
  if (remember)
    {
      time_t tomorrow = time(NULL) + 24 * 60 * 60;
      char time_buf[64] = "";
      strftime(time_buf, sizeof time_buf / sizeof time_buf[0],
	       "%a, %d %b %Y %H:%M:%S GMT", gmtime(&tomorrow));
      
      snprintf(cookie_header,
	       sizeof(cookie_header) / (sizeof(cookie_header[0])),
	       "Set-Cookie: UserId=%d; path=/; expires='%s'\n",
	       user_id, time_buf);
    }
  else
    {
      snprintf(cookie_header,
	       sizeof(cookie_header) / (sizeof(cookie_header[0])),
	       "Set-Cookie: UserId=%d; path=/\n",
	       user_id);
    }
  session_redirect("/", cookie_header);
}

static void login_fail(void)
{
  session_redirect("/site/login", NULL);
}

static void controller_site_action_login(void)
{
  const char *content_length = getenv("CONTENT_LENGTH");
  if (content_length == NULL)
    {
      render_site_login();
      return;
    }
  else
    {
      char content[MAX_CONTENT_LEN + 1] = {'\0'};
      int length = atoi(content_length);
      fgets(content, length + 1, stdin);
      char username[MAX_USERNAME_LEN + 1] = {'\0'};
      char password[MAX_PASSWORD_LEN + 1] = {'\0'};
      char remember[16] = "";
      unescape_url(content);
      sscanf(content,
	     "login=%15[^&]&password=%15[^&]&remember=%15s",
	     username, password, remember);
      const int user_id = model_user_find_user_id(username, password);
      if (user_id > 0)
	login_success(user_id, strcmp(remember, "") != 0);
      else
	login_fail();
    }
}

static void controller_site_action_index(void)
{
  const int user_id = session_get_curr_user_id();
  struct Model_user *user = model_user_select_by_id(user_id);
  struct Model_bulletins *bulletins =
    select_bulletins_by_status("public");
  if (user)
    render_site_index(user->username, bulletins);
  else
    render_site_index_guest(bulletins);
  free(bulletins);
  model_user_free(user);
}

static void controller_site_action_logout(void)
{
  char cookie_header[128] = "";
  snprintf(cookie_header,
	   sizeof(cookie_header) / (sizeof(cookie_header[0])),
	   "Set-Cookie: UserId=%d; path=/;"
	   " expires=Thu, 01 Jan 1970 00:00:00 GMT\n",
	   session_get_curr_user_id());
  session_redirect("/", cookie_header);
}

void controller_site_action(const char *request_uri)
{
  if (strcmp(request_uri, "/site/login") == 0)
    controller_site_action_login();
  else if (strcmp(request_uri, "/site/logout") == 0)
    controller_site_action_logout();
  else
    controller_site_action_index();
}
