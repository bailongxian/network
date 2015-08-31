#include <my_global.h>
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	MYSQL *conn;
	conn = mysql_init(NULL);
	if(conn == NULL)
	{
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}

	if(mysql_real_connect(conn, "localhost", "bailongxian", "blx",
		NULL, 0, NULL, 0) == NULL)
	{
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}

	char query[] = "create database testdb";
	if(mysql_real_query(conn, query, sizeof(query)))
	{
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}

	mysql_close(conn);
	return 0;
}
