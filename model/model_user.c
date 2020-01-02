#include <mysql.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "model_db.h"
#include "model_user.h"

struct Model_user* model_user_select_by_id(int id)
{
  MYSQL *conn = NULL;
  MYSQL_RES *result = NULL;
  MYSQL_ROW row;
  char query[256];
  conn = mysql_init(NULL);
  mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0);
  snprintf(query, sizeof query / sizeof query[0],
	   "SELECT `id`, `username`, `password`, `auth_key`, `access_token` "
	   "FROM `user` WHERE "
	   "`id`=%d;", id);
  mysql_query(conn, query);
  result = mysql_store_result(conn);
  row = mysql_fetch_row(result);
  struct Model_user *user = calloc(1, sizeof(struct Model_user));
  user->id = atoi(row[0] ? row[0]: "");
  strcpy(user->username, row[1] ? row[1]: "");
  strcpy(user->password, row[2] ? row[2]: "");
  strcpy(user->auth_key, row[3] ? row[3]: "");
  strcpy(user->access_token, row[4] ? row[4]: "");
  mysql_free_result(result);
  mysql_close(conn);
  return user;
}

void model_user_free(struct Model_user *model)
{
  free(model);
}
