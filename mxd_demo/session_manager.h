#pragma once

#ifndef __SESSION_MANAGER_H__
#define __SESSION_MANAGER_H__

#include "var.h"

#include <stdio.h>
#include <map>

using namespace std;

class SessionManager
{
public:
	SessionManager();
	~SessionManager();

	void SetSession(e_session_key_type k, int v);
	int GetSession(e_session_key_type k);
	void DeleteSession(e_session_key_type k);
	void ClearSession();

private:
	map<e_session_key_type, int> _session;
};

#endif // !__SESSION_MANAGER_H__

