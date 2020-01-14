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
