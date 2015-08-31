#include "Mysql_Conn_Pool.h"
#include "Mysql_Conn.h"
#include "Mysql_Task.h"

CMysql_Con_Pool::CMysql_Con_Pool(int default,int max,int min, 
const string& Host, const string& User, const string& pwd):
	Default_(default),
	Max_(max),
	Min_(min),
	strHost_(Host),
	strUser_(User),
	strPwd_(pwd)
{
}

CMysql_Con_Pool::~CMysql_Con_Pool()
{
	Destroy();
}

void CMysql_Con_Pool::Init()
{
	for(int i = 0; i < Default_; i++)
	{
		CMysql_con *Conn = new CMysql_con(strHost_, strUser_, strUser_);
		CurrenConList_.push_back(Conn);
	}
}

void CMysql_Con_Pool::Destroy()
{
	std::list<CMysql_con*>::iterator it = CurrenConList_.begin();
	for(; it != CurrenConList_.end();)
	{	
		delete *it;
		it = CurrenConList_.erase(it);
	}
}

CMysql_con* CMysql_Con_Pool::GetOneIdleCon()
{
	std::List<CMysql_con*>::iterator it = CurrenConList_.begin();
	for(; it != CurrenConList_.end(); ++it)
	{
		CMysql_con* pCon = *it;
		if(pCon->GetState() == CMysql_con::CON_IDLE)
		{
			pCon->SetState(CMysql_con::CON_BUSYING);
			return pCon;
		}
	}
	return NULL;
}

void CMysql_Con_Pool::FreeOneCon(CMysql_con * Conn)
{
	assert(Conn->GetState() == CMysql_con::CON_BUSYING);
	Conn->SetState(CMysql_con::CON_IDLE);
}