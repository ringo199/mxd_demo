
#include "session_manager.h"


SessionManager::SessionManager()
{
}

SessionManager::~SessionManager()
{
}

void SessionManager::SetSession(e_session_key_type k, int v)
{
	this->_session[k] = v;
}

int SessionManager::GetSession(e_session_key_type k)
{
	return this->_session[k];
}

void SessionManager::DeleteSession(e_session_key_type k)
{
	this->_session[k] = -1;
}

void SessionManager::ClearSession()
{
	_session.clear();
}
