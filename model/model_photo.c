#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql.h>
#include "model_db.h"
#include "model_photo.h"
#include "../controller/session.h"

#define MAX_CONTENT_LEN 3200
#define MAX_FIELD_LEN 255

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

void model_photo_set_new(
			 struct Model_photo *photo,
			 const struct Model_photoform *form,
			 int bull_id
			 )
{
  memset(photo, '\0', sizeof(struct Model_photo));
  photo->bull_id = bull_id;
  if (form->link)
    strcpy(photo->link, form->link);
  if (form->info)
    strcpy(photo->info, form->info); 
}

int model_photo_insert(const struct Model_photo *photo)
{
  if (!photo)
    return 0;
  char query[2048];
  MYSQL *conn = mysql_init(NULL);
  mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0);
  mysql_query(conn, "set names utf8");
  snprintf(query, sizeof query / sizeof query[0],
	   "INSERT INTO `photo`"
	   "(`bull_id`,`link`,`info`)"
	   " VALUES ('%d', '%s', '%s');",
	   photo->bull_id, photo->link, photo->info);
  mysql_query(conn, query);
  mysql_close(conn);
  return 1;
}

int model_photo_update_info_by_id(const struct Model_photo *photo)
{
  if (!photo)
    return 0;
  char query[2048];
  MYSQL *conn = mysql_init(NULL);
  mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0);
  mysql_query(conn, "set names utf8");
  snprintf(query, sizeof query / sizeof query[0],
	   "UPDATE `photo`"
	   " SET `info`='%s'"
	   " WHERE `id`='%d';",
	   photo->info, photo->id);
  mysql_query(conn, query);
  mysql_close(conn);
  return 1;
}

int model_photo_load_info_by_post(struct Model_photo *photo)
{
  const char *content_length = getenv("CONTENT_LENGTH");
  if (content_length == NULL)
      return 0;
  char content[MAX_CONTENT_LEN + 1] = {'\0'};
  int length = atoi(content_length);
  fgets(content, length + 1, stdin);
  unescape_url(content);
  sscanf(content, "id=%d&info=%255[^&]", &photo->id, photo->info);
  return 1;
}
