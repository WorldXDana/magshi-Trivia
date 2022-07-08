#include "server.h"

void server::run()
{

	// Q: why is this try necessarily ?
// A: we want to know what happened that made the server crush
	try
	{
		TRACE("Starting...");
		// NOTICE at the end of this block the WSA will be closed 
		//this->m_communicator.bindAndListen();
		std::thread t_commuincation(&Communicator::bindAndListen, std::ref(this->m_communicator));
		t_commuincation.detach();

		//HAVE A LOOP GO OUT AND COUNT WHATEVER U NEED TO DO
		string input;
		cin >> input;
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception was thrown in function: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unknown exception in main !" << std::endl;
	}
}

server::server(IDatabase* database) :
	m_database(database), m_handlerFactory(database), m_communicator(m_handlerFactory)
{
	
}
