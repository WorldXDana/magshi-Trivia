#pragma once
#include "LoginManager.h"

class LoginManager;

class LoggedUser
{

public:
    LoggedUser(string username);
    string getUsername();
    friend bool operator == (const LoggedUser& first, const LoggedUser& second);
private:
    string m_username;

};

