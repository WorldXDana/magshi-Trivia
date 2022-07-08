#pragma once

#include "MenuRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
	public:
		RequestHandlerFactory(IDatabase* database);
		RequestHandlerFactory();
		RequestHandlerFactory(const RequestHandlerFactory& factory);
		~RequestHandlerFactory();

		LoginRequestHandler* createLoginRequestHandler();
		MenuRequestHandler* createMenuRequestHandler(std::string username);

	private:
		LoginManager m_loginManager;
		RoomManager m_roomManager;
		StatisticsManager m_highscoreTable;
};

