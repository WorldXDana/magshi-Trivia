#include "Communicator.h"
#include "WSAInitializer.h"
#include "helper.h"


class server
{
public:
	void run();
	server(IDatabase* database);
private:
	IDatabase* m_database;
	RequestHandlerFactory m_handlerFactory;
	Communicator m_communicator;
};


