#pragma once
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
class RoomMemberRequestHandler
{
public:
	bool isRequestRelevant(string RequestInfo);
	RequestResult handleRequest(string RequestInfo);
	

private:
	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;
	RequestResult leaveRoom(string RequestInfo);
	RequestResult getRoomState(string RequestInfo);

};

