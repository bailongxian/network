#include "Mysql_Conn.h"


CMysql_con::CMysql_con(const string & host,const string & user,const string & pswd)
{
	Conn_ = mysql_init(NULL);
	if(Conn_ == NULL)
	{
		Error();
		exit(-1);
	}

	if(mysql_real_connect(Conn_, host.c_str(), user.c_str(), pswd.c_str(),
		NULL, 0, NULL, 0) == NULL)
	{
		Error();
		exit(1);
	}
}

CMysql_con::~Mysql_con()
{
	mysql_close(Conn_);
}

void CMysql_con::Error()
{
	printf("Error %u: %s\n", mysql_errno(Conn_), mysql_error(Conn_));
}

void CMysql_con::Execute(const string & strsql)
{
	mysql_real_query(Conn_, strsql.c_str(), strsql.size());
}

void CMysql_con::Execute(const char * buff,size_t len)
{
	mysql_real_query(Conn_, buff, len);
}