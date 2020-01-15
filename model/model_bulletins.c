#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql.h>
#include "model_db.h"
#include "model_bulletins.h"

void model_bulletins_set_new(
			    struct Model_bulletins *bulletin,
			    const struct Model_bulletinsform *form,
			    int session_user_id			    
			    )
{
  memset(bulletin, '\0', sizeof(struct Model_bulletins));
  bulletin->user_id = session_user_id;
  strcpy(bulletin->title, form->title);
  strcpy(bulletin->info, form->info);
  strcpy(bulletin->contacts, form->contacts);
  strcpy(bulletin->city, form->city);
  bulletin->price = form->price;
  strcpy(bulletin->status, "wait");
}

int model_bulletins_save(const struct Model_bulletins *bulletin)
{
  if (!bulletin)
    return 0;
  char query[2048];
  MYSQL *conn = mysql_init(NULL);
  mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0);
  mysql_query(conn, "set names utf8");
  snprintf(query, sizeof query / sizeof query[0],
	   "INSERT INTO `bulletins`"
	   "(`user_id`,`title`,`info`,`contacts`,`city`,`price`,`status`)"
	   " VALUES ('%d', '%s', '%s', '%s', '%s', '%f', '%s')",
	   bulletin->user_id, bulletin->title, bulletin->info,
	   bulletin->contacts, bulletin->city, bulletin->price,
	   bulletin->status);
  mysql_query(conn, query);
  mysql_close(conn);
  return 1;
}

struct Model_bulletins *
select_bulletins_by_userid_and_status(int user_id, const char *status)
{
  if (user_id <= 0 || status == NULL)
    return NULL;
  MYSQL *conn = NULL;
  MYSQL_RES *result = NULL;
  MYSQL_ROW row;
  char query[2048] = {'\0'};
  conn = mysql_init(NULL);
  mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0);
  mysql_query(conn, "set names utf8");
  snprintf(query, sizeof query / sizeof query[0],
	   "SELECT `id`,`user_id`,`date_pub`,`title`,"
	   "`info`,`contacts`,`city`,`price`,`status`"
	   "FROM `bulletins` WHERE "
	   "`user_id`=%d AND `status`='%s';", user_id, status);
  mysql_query(conn, query);
  result = mysql_store_result(conn);
  struct Model_bulletins *bulletins =
    calloc(mysql_num_rows(result) + 1, sizeof(struct Model_bulletins));
  int i = 0;
  while ((row = mysql_fetch_row(result)))
    {
      bulletins[i].id = atoi(row[0]);
      bulletins[i].user_id = atoi(row[1]);
      strcpy(bulletins[i].date_pub, row[2] ? row[2] : "");
      strcpy(bulletins[i].title, row[3] ? row[3] : "");
      strcpy(bulletins[i].info, row[4] ? row[4] : "");
      strcpy(bulletins[i].contacts, row[5] ? row[5] : "");
      strcpy(bulletins[i].city, row[6] ? row[6] : "");
      bulletins[i].price = atof(row[7]);
      ++i;
    }
  mysql_free_result(result);
  mysql_close(conn);
  return bulletins;
}
