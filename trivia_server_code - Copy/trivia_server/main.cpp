// trivia_server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#pragma comment (lib, "ws2_32.lib")
#include <iostream>
#include "WSAInitializer.h"
#include "helper.h"
#include "server.h"
#include "SqliteDataBase.h"
#include "LoginManager.h"

std::map<string, int> user_log;

int main()
{
	try
	{
		SqliteDataBase* db = new SqliteDataBase();
		WSAInitializer wsa_init;
		db->open();
		server trivia(db);
		trivia.run();
		return 1;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}


