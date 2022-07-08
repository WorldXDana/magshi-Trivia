#pragma once
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
class RoomAdminRequestHandler
{
public:
	bool isRequestRelevant(string RequestInfo);
	RequestResult handleRequest(string RequestInfo);

private:
	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;
	RequestResult closeRoom(string RequestInfo);
	RequestResult startGame(string RequestInfo);
	RequestResult getRoomState(string RequestInfo);

};

