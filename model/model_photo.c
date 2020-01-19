#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql.h>
#include "model_db.h"
#include "model_photo.h"

void model_photo_free(struct Model_photo *photo)
{
  free(photo);
}

struct Model_photo *select_photos_by_bull_id(int bull_id)
{
  if (bull_id <= 0)
    return NULL;
  MYSQL *conn = NULL;
  MYSQL_RES *result = NULL;
  MYSQL_ROW row;
  char query[2048] = {'\0'};
  conn = mysql_init(NULL);
  mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0);
  mysql_query(conn, "set names utf8");
  snprintf(query, sizeof query / sizeof query[0],
	   "SELECT `id`,`bull_id`,`link`,`info` "
	   "FROM `photo` WHERE "
	   "`bull_id`=%d;",
	   bull_id);
  mysql_query(conn, query);
  result = mysql_store_result(conn);
  struct Model_photo *photos =
    calloc(mysql_num_rows(result) + 1, sizeof(struct Model_photo));
  int i = 0;
  while ((row = mysql_fetch_row(result)))
    {
      photos[i].id = atoi(row[0]);
      photos[i].bull_id = atoi(row[1]);
      strcpy(photos[i].link, row[2] ? row[2] : "");
      strcpy(photos[i].info, row[3] ? row[3] : "");
      ++i;
    }
  mysql_free_result(result);
  mysql_close(conn);
  return photos;
}
