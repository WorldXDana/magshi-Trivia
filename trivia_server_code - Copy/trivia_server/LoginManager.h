#pragma once
#include <vector>
#include "IDatabase.h"
#include "LoggedUser.h"

class LoggedUser;

class LoginManager
{
public:
	LoginManager(IDatabase* idatabase);
	LoginManager();
	bool signup(string username, string password, string email);
	bool login(string username, string password);
	void logout(string user);
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
};

