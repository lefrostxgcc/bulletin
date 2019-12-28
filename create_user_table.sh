#!/bin/sh

DATABASE='bulletinsdb'
TABLE='user'
SQL_CREATE_TABLE="CREATE TABLE $TABLE("
SQL_CREATE_TABLE+="id int auto_increment primary key,"
SQL_CREATE_TABLE+="username varchar(255) charset utf8,"
SQL_CREATE_TABLE+="password varchar(255) charset utf8,"
SQL_CREATE_TABLE+="auth_key varchar(255) charset utf8,"
SQL_CREATE_TABLE+="access_token varchar(255) charset utf8"
SQL_CREATE_TABLE+=") default charset utf8;"
SQL_QUERY=$SQL_CREATE_TABLE

mysql -u root -p --database="$DATABASE" -e "$SQL_QUERY"
