#ifndef _MYSQL_CONN_H_
#define _MYSQL_CONN_H_

#include<my_global.h>
#include<mysql.h>

class CTask;


class CMysql_con
{
	CMysql_con(const string& host, const string& user, const string& pswd);
	~Mysql_con();

	void Error();
	void Execute(const string& strsql);
	void Execute(const char* buff, size_t len);

	enum CON_STATE
	{
		CON_INIT = 0,
		CON_IDLE,
		CON_BUSYING
	};

	void SetState(CON_STATE state) {State_ = state;}
	CON_STATE GetState() {return State_;}
	
private:	
	MYSQL *Conn_;
	CON_STATE State_;
};

#endif
