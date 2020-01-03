#include <stdio.h>
#include "view_site.h"

static void show_header()
{
  printf("%s", "Set-Cookie: UserName=chip; path=/; expires=Thu, 01 Jan 1970 00:00:00 GMT");
  printf("%s", "Content-Type: text/html\n\n");
  printf("%s", "<!DOCTYPE html><html>");
  printf("%s", "<head>");
  printf("%s", "<meta http-equiv=\"Refresh\" content=\"0; url=/site/index\" />");
  printf("%s", "</head><body>");
}

static void show_footer()
{
  printf("</body></html>");
  printf("\n\n");
}

void render_site_logout(void)
{
  show_header();
  show_footer();
}
