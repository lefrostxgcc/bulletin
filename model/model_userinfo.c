#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <mysql.h>
#include "model_db.h"
#include "model_userinfo.h"

struct Model_userinfo* model_userinfo_select_by_user_id(int user_id)
{
  MYSQL *conn = NULL;
  MYSQL_RES *result = NULL;
  MYSQL_ROW row;
  char query[256];
  conn = mysql_init(NULL);
  mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0);
  snprintf(query, sizeof query / sizeof query[0],
	   "SELECT `id`, `user_id`, `surname`, `name`, `middlename` "
	   "FROM `userinfo` WHERE "
	   "`user_id`=%d;", user_id);
  mysql_query(conn, query);
  result = mysql_store_result(conn);
  row = mysql_fetch_row(result);
  if (!row)
    return NULL;
  struct Model_userinfo *userinfo = calloc(1, sizeof(struct Model_userinfo));
  userinfo->id = atoi(row[0] ? row[0]: "");
  userinfo->user_id = atoi(row[1] ? row[1]: "");
  strcpy(userinfo->surname, row[2] ? row[2]: "");
  strcpy(userinfo->name, row[3] ? row[3]: "");
  strcpy(userinfo->middlename, row[4] ? row[4]: "");
  mysql_free_result(result);
  mysql_close(conn);
  return userinfo;
}

void model_userinfo_free(struct Model_userinfo *userinfo)
{
  free(userinfo);
}
