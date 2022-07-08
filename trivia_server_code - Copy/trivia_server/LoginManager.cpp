#include "LoginManager.h"

LoginManager::LoginManager(IDatabase* idatabase)
{
	this->m_database = idatabase;
}

LoginManager::LoginManager()
{
}

bool LoginManager::signup(string username, string password, string email)
{
	bool check;
	LoggedUser user(username);
	check = this->m_database->addNewUser (username, password, email);
	if (check == true)
	{
		this->m_loggedUsers.push_back(user);
	}
	else 
	{
		return false;
	}
}

bool LoginManager::login(string username, string password)
{
	LoggedUser user(username);
	if (this->m_database->doesUserExist(username) && this->m_database->doesPasswordMatch(username, password))
	{
		this->m_loggedUsers.push_back(user);
		return true;
	}
	return false;
}

void LoginManager::logout(string user)
{
	this->m_loggedUsers.erase(std::remove(this->m_loggedUsers.begin(), this->m_loggedUsers.end(), user), this->m_loggedUsers.end());
}
