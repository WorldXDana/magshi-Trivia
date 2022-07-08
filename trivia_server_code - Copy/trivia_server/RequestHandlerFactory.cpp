#include "RequestHandlerFactory.h"


RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) : m_loginManager(database), m_highscoreTable(database)
{
}

RequestHandlerFactory::RequestHandlerFactory()
{
}

RequestHandlerFactory::RequestHandlerFactory(const RequestHandlerFactory& factory):
	m_loginManager(factory.m_loginManager), m_roomManager(factory.m_roomManager), m_highscoreTable(factory.m_highscoreTable)
{

}

RequestHandlerFactory::~RequestHandlerFactory()
{
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(m_loginManager, this);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(std::string username)
{
	return new MenuRequestHandler (username, m_roomManager, m_highscoreTable, this);
}
