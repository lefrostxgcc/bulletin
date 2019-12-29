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
	 "<form action=\"auth\" method=\"post\">"
	 "<table><tr>"
	 "<td><label>Login:</label></td>"
	 "<td><input name=\"login\" size=\"15\"></td>"
	 "</tr><tr>"
	 "<td><label>Password:</label></td>"
	 "<td><input name=\"password\" size=\"15\"></td>"
	 "</tr><tr>"
	 "<td><input type=\"submit\" value=\"Login\"></td></tr>"
	 "</table>"
	 "</form>"
	 );
}

static inline void print_welcome_page(const char *username)
{
  printf("%s %s %s",
	 "<div><h2> Привет",
	 username,
	 "!</h2></div>"
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

static inline void print_content_length_error(void)
{
  print_index_page();
  printf("%s", "<div>Ошибка передачи данных из формы<div>");
}

static inline void print_login_error_page(void)
{
  print_index_page();
  printf("%s", "<div>Ошибка! Неверное имя пользователя или пароль<div>");
}

static int is_correct_user_pass(const char *username, const char *password)
{
  MYSQL *conn = NULL;
  MYSQL_RES *result = NULL;
  MYSQL_ROW row;
  char query[256];
  unsigned char md5digest[MD5_DIGEST_LENGTH + 1] = {'\0'};
  MD5((const unsigned char *)password, strlen(password), md5digest);
  char md5pass[64] = {'\0'};
  for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
    snprintf(md5pass + i * 2, 3, "%02x", md5digest[i]);
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
  return count;
}

static void do_auth(void)
{
  const char *content_length = getenv("CONTENT_LENGTH");
  int length = 0;
  if (content_length == NULL || (length = atoi(content_length)) <= 0)
    {
      print_content_length_error();
      return;
    }
  char content[MAX_CONTENT_LEN + 1];
  if (fgets(content, length + 1, stdin) == NULL)
    {
      print_content_length_error();
      return;
    }
  char username[MAX_USERNAME_LEN + 1] = {'\0'};
  char password[MAX_PASSWORD_LEN + 1] = {'\0'};
  if (sscanf(content, "login=%15[^&]&password=%15s", username, password) != 2)
    {
      print_content_length_error();
      return;
    }
  if (is_correct_user_pass(username, password))
    print_welcome_page(username);
  else
    print_login_error_page();
}

int main(void)
{
  const char *request_uri = getenv("REQUEST_URI");
  printf("%s", "Content-Type: text/html\n\n");
  printf("%s", "<!DOCTYPE html><html>");
  printf("%s", "<head><style>.centered { position: fixed;"
	 "top: 50%; left: 50%; transform: translate(-50%, -50%);}"
	 "</style></head><body>");
  printf("%s", "<div class=centered><div><h1>Доска объявлений</h1></div>");
  printf("%s", "<a href=\"/\">На главную страницу</a>");
  if (strcmp(request_uri, "/login") == 0)
      print_login_form();
  else if (strcmp(request_uri, "/auth") == 0)
      do_auth();
  else
      print_index_page();
  printf("</div></body></html>");
  printf("\n\n");
}
