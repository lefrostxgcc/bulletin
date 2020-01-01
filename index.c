#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include <openssl/md5.h>
#include "controller/controller_user.h"

#define MAX_USERNAME_LEN 15
#define MAX_PASSWORD_LEN 15
#define MAX_CONTENT_LEN 63
#define DB_HOST "localhost"
#define DB_NAME "bulletinsdb"
#define DB_USER "root"
#define DB_PASS "Video#13417"

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
}

static inline void print_content_length_error(void)
{
  print_index_page();
  printf("%s", "<div>Ошибка передачи данных из формы</div>");
}

static inline void print_login_error_page(void)
{
  print_index_page();
  printf("%s", "<div>Ошибка! Неверное имя пользователя или пароль</div>");
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
  mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0);
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
  printf("%s", "<head>");
  printf("%s", "<link rel=\"stylesheet\" href=\"/styles.css\">");
  printf("%s", "</head><body>");
  printf("%s", "<header><nav class=\"top-menu\">");
  printf("%s", "<ul class=\"menu-main\">");
  printf("%s", "<li class=\"left-item\"><a href=\"/\">Доска объявлений</a></li>");
  printf("%s", "<li class=\"right-item\"><a href=\"/login\">Вход</a></li>");
  printf("%s", "<li class=\"right-item\"><a href=\"/user/index\">Информация о пользователе</a></li>");

  printf("%s", "</ul></nav></header>");
  if (strcmp(request_uri, "/login") == 0)
    print_login_form();
  else if (strcmp(request_uri, "/auth") == 0)
    do_auth();
  else if (strcmp(request_uri, "/user/index") == 0)
    controller_user_action(request_uri);
  else
    print_index_page();
  printf("</body></html>");
  printf("\n\n");
}
