#pragma once
#include <deque>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "helper.h"
#include "LoginRequestHandler.h"

static const unsigned short PORT = 8826;
static const unsigned int IFACE = 0;

class Communicator
{
public:
	Communicator(RequestHandlerFactory& factory);
	~Communicator();
	void bindAndListen();

private:
	void acceptClient();
	void clientHandler(SOCKET client_socket);

	
	SOCKET _socket;
	std::mutex m_clientsMutex;
	std::mutex m_userLog;
	RequestHandlerFactory m_factory;
	std::map< SOCKET, IRequestHandler*> _Users;
};

