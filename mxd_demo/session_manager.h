#pragma once

#ifndef __SESSION_MANAGER_H__
#define __SESSION_MANAGER_H__

#include "var.h"

#include <stdio.h>
#include <unordered_map>
#include <string>

using namespace std;

class SessionManager
{
public:
	SessionManager();
	~SessionManager();

	void SetSession(e_session_key_type k, int v);
	void SetSession(e_session_key_type k, string v);
	int GetSession(e_session_key_type k);
	string GetSession_String(e_session_key_type k);
	void DeleteSession(e_session_key_type k);
	void ClearSession();

private:
	unordered_map<e_session_key_type, int> _session;
	unordered_map<e_session_key_type, string> _session_str;
};

#endif // !__SESSION_MANAGER_H__

