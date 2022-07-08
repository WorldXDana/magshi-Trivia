#pragma once
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
//#include "JsonRequestPacketDeserializer.h"
#include "LoginRequestHandler.h"
//#include "JsonResponsePacketSerializer.h"
#include "LoggedUser.h"

class JsonResponsePacketSerializer;
class JsonResponsePacketDesrializer;
class RequestHandlerFactory;

class MenuRequestHandler :
    public IRequestHandler
{
public:
    bool isRequestRelevant(Request request);
    RequestResult handleRequest(Request request);
    MenuRequestHandler(std::string username, RoomManager rm, StatisticsManager ht, RequestHandlerFactory* rhf);
private:
    LoggedUser m_users;
    RoomManager m_roomManager;
    StatisticsManager m_statisticsManager;
    RequestHandlerFactory* m_handlerFactory;
    
    RequestResult signout(Request request);
    RequestResult getRooms(Request request);
    RequestResult getPlayersInRoom(Request request);
    RequestResult getHighscores(Request request);
    RequestResult joinRoom(Request request);
    RequestResult createRoom(Request request);

};

