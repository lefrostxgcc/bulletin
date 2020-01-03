#include <stdio.h>
#include "view_site.h"

static void show_header(int user_id)
{
  printf("Set-Cookie: UserId=%d; path=/;"
	 " expires=Thu, 01 Jan 1970 00:00:00 GMT", user_id);
  printf("%s", "Content-Type: text/html\n\n");
  printf("%s", "<!DOCTYPE html><html>");
  printf("%s", "<head>");
  printf("%s", "<meta http-equiv=\"Refresh\""
	 " content=\"0; url=/site/index\" />");
  printf("%s", "</head><body>");
}

static void show_footer()
{
  printf("</body></html>");
  printf("\n\n");
}

void render_site_logout(int user_id)
{
  show_header(user_id);
  show_footer();
}
