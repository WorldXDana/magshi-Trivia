#include "LoggedUser.h"

LoggedUser::LoggedUser(string username)
{
}

string LoggedUser::getUsername()
{
	return this->m_username;
}

bool operator==(const LoggedUser & first, const LoggedUser & second)
{
	return first.m_username == second.m_username;
}
