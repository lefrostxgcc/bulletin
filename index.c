#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include <openssl/md5.h>

#define MAX_USERNAME_LEN 15
#define MAX_PASSWORD_LEN 15
#define MAX_CONTENT_LEN 63

static inline void print_login_form(void)
{
  printf("%s",
	 "<form action=\"welcome\" method=\"post\">"
	 "<div>"
	 "<label>Login:</label><input name=\"login\" size=\"15\">"
	 "</div>"
	 "<div>"
	 "<label>Password:</label><input name=\"password\" size=\"15\">"
	 "</div>"
	 "<div>"
	 "<input type=\"submit\" value=\"Login\">"
	 "</div>"
	 "</form>"
	 );
}

static inline void print_welcome_page(const char *username)
{
  printf("%s %s %s",
	 "<div> Привет",
	 username,
	 "!</div>"
	 "<div>"
	 "<a href=\"/\">Выход</a>"
	 "</div>"
	 );
}

static inline void print_index_page(void)
{
  printf("%s",
	 "<div>"
	 "<a href=\"login\">Вход</a>"
	 "</div>"
	 );
}

int main(void)
{
  const char *request_uri = getenv("REQUEST_URI");
  char username[MAX_USERNAME_LEN + 1] = {'\0'};
  char password[MAX_PASSWORD_LEN + 1] = {'\0'};
  char content[MAX_CONTENT_LEN + 1];
  printf("%s", "Content-Type: text/html\n\n");
  printf("%s", "<!DOCTYPE html><html><body>");
  printf("%s", "<h1>Доска объявлений</h1>");
  printf("%s", "<a href=\"/\">На главную страницу</a>");
  if (strcmp(request_uri, "/login") == 0)
    {
      print_login_form();
    }
  else if (strcmp(request_uri, "/welcome") == 0)
    {
      const char *content_length = getenv("CONTENT_LENGTH");
      int length = 0;
      if (content_length == NULL || (length = atoi(content_length)) <= 0)
	print_login_form();
      else
	{
	  fgets(content, length + 1, stdin);
	  sscanf(content, "login=%15[^&]&password=%15s", username, password);
	  unsigned char md5digest[MD5_DIGEST_LENGTH + 1] = {'\0'};
	  MD5((const unsigned char *)password, strlen(password), md5digest);
	  char md5pass[64] = {'\0'};
	  for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
	    snprintf(md5pass + i * 2, 3, "%02x", md5digest[i]);
	  MYSQL *conn = NULL;
	  MYSQL_RES *result = NULL;
	  MYSQL_ROW row;
	  char query[256];
	  conn = mysql_init(NULL);
	  mysql_real_connect(conn, "localhost", "root", "Video#13417",
			     "bulletinsdb", 0, NULL, 0);
	  snprintf(query, 256, "SELECT COUNT(id) FROM user WHERE "
		   "username='%s' AND password='%s';", username, md5pass);
	  mysql_query(conn, query);
	  result = mysql_store_result(conn);
	  row = mysql_fetch_row(result);
	  int count = atoi(row[0]);
	  mysql_free_result(result);
	  mysql_close(conn);
	  if (count == 1)
	    print_welcome_page(username);
	  else
	    print_index_page();
	}
    }
  else
    {
      print_index_page();
    }
  printf("</body></html>");
  printf("\n\n");
}
