#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  const char *uri = getenv("REQUEST_URI");
  printf("Content-Type: text/html\n\n");
  printf("%s %s %s",
	 "<!DOCTYPE html>"
	 "<html>"
	 "<style type=\"text/css\">"
	 ".centerDiv"
	 "{"
	 "position: fixed; top: 50%; left: 50%;"
	 "transform: translate(-50%, -50%);"
	 "color: #000080;"
	 "}"
	 "</style>"
	 "<body>"
	 "<div class=\"centerDiv\">"
	 "<h1> REQUEST_URI: \"",
	 uri,
	 "\"<h1>"
	 "</div>"
	 "</body>"
	 "</html>"
	 );
  printf("\n\n");
}
