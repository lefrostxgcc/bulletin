#include <stdio.h>

int main(void)
{
  printf("Content-Type: text/html\n\n");
  printf(
	 "<!DOCTYPE html>"
	 "<html>"
	 "<style type=\"text/css\">"
	 ".centerDiv"
	 "{"
	 "position: fixed; top: 50%%; left: 50%%;"
	 "transform: translate(-50%%, -50%%);"
	 "color: #000080;"
	 "}"
	 "</style>"
	 "<body>"
	 "<div class=\"centerDiv\">"
	 "<h1>Hello Videosharp Web Bulletin Board!</h1>"
	 "</div>"
	 "</body>"
	 "</html>"
	 );
  printf("\n\n");
}
