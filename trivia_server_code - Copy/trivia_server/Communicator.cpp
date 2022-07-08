#include "Communicator.h"

Communicator::Communicator(RequestHandlerFactory& factory) : m_factory(factory)
{
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		throw std::runtime_error("Failed to startup WSA");
	}

	std::cout << "WSA Initialized" << std::endl;

	_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_socket == INVALID_SOCKET)
	{
		throw std::runtime_error("Failed to create socket");
	}

	std::cout << "Server socket ready" << std::endl;
}

Communicator::~Communicator()
{
	TRACE(__FUNCTION__ " closing accepting socket");
	// why is this try necessarily ?
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		::closesocket(_socket);
	}
	catch (...) {}
}

void Communicator::clientHandler(SOCKET client_socket)
{
	std::string str = "got in\n";
	while (true) {

		try {
			auto messageDev = helper::reciveInformationFromSocket(client_socket);

			Request request = {
				messageDev.code,
				std::time(nullptr),
				messageDev.data
			};

			IRequestHandler* handler = nullptr;
			handler = this->_Users.find(client_socket)->second;

			if (handler->isRequestRelevant(request)) {
				RequestResult res = handler->handleRequest(request);
				std::lock_guard<std::mutex> locker(m_clientsMutex);
				delete[] _Users.find(client_socket)->second;
				_Users.find(client_socket)->second = res.newHandler;
				send(client_socket, res.response.data(), res.response.size(), 0);

			}

			else {
				ErrorResponse response = { "Invalid request type" };
				std::vector<char> packet = JsonResponsePacketSerializer::serializeResponse(response);
				send(client_socket, packet.data(), packet.size(), 0);
			}

		}


		catch (const std::exception& e) {
			std::cout << "Exception was catch in function clientHandler. socket=" << client_socket << ", what=" << e.what() << std::endl;
			std::lock_guard<std::mutex> locker(m_clientsMutex);
			delete[] _Users.find(client_socket)->second;
			_Users.erase(_Users.find(client_socket));
			closesocket(client_socket);
			break;
		}

	}
	closesocket(client_socket);
}


void Communicator::bindAndListen()
{
	_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");

	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(PORT);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = IFACE;
	// again stepping out to the global namespace
	if (::bind(_socket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
	TRACE("binded");

	if (::listen(_socket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	TRACE("listening...");

	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		TRACE("accepting client...");
		acceptClient();
	}
}

void Communicator::acceptClient()
{
	SOCKET client_socket = accept(_socket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	TRACE("Client accepted !");
	// create new thread for client	and detach from it
	std::lock_guard<std::mutex> locker(this->m_clientsMutex);
	this->_Users[client_socket] = (IRequestHandler*)m_factory.createLoginRequestHandler();
	std::thread tr(&Communicator::clientHandler, this, client_socket);
	tr.detach();
}
