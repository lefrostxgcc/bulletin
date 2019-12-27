#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  const char *request_uri = getenv("REQUEST_URI");
  printf("Content-Type: text/html\n\n");
  printf("%s %s %s",
	 "<!DOCTYPE html>"
	 "<html>"
	 "<body>"
	 "<h1> REQUEST_URI: \"", request_uri, "\"</h1>"
	 "</body>"
	 "</html>"
	 );
  printf("\n\n");
}
