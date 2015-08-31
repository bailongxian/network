#ifndef _MYSQL_CON_POOL_
#define _MYSQL_CON_POOL_

#include<list>
#include"Mysql_Conn.h"

class CMysql_Con_Pool
{
public:
	CMysql_Con_Pool(int default, int max, int min);
	~CMysql_Con_Pool();

private:
	void Init();
	void Destroy();
	CMysql_con* GetOneIdleCon();
	void FreeOneCon(CMysql_con* Conn);
private:
	int Default_;
	int Max_;
	int Min_;

	std::string strHost_;
	std::string strUser_;
	std::string strPwd_;

	std::List<CMysql_Conn*> CurrenConList_;
};

#endif