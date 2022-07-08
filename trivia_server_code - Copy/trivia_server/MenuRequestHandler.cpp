#include "MenuRequestHandler.h"

bool MenuRequestHandler::isRequestRelevant(Request request)
{
	int id = request.id;
	return id == GET_PLAYERS_IN_ROOM_REQUEST || id == JOIN_ROOM_REQUEST || id == CREATE_ROOM_REQUEST || id == LOGOUT_REQUEST || id == GET_ROOMS_REQUEST || id == GET_HIGH_SCORE_REQUEST;
}

RequestResult MenuRequestHandler::handleRequest(Request request)
{
	RequestResult result;
	try {
		if (request.id == GET_PLAYERS_IN_ROOM_REQUEST) {
			result = getPlayersInRoom(request);
		}
		else if (request.id == CREATE_ROOM_REQUEST) {
			result = createRoom(request);
		}
		else if (request.id == GET_HIGH_SCORE_REQUEST) {
			result = createRoom(request);
		}
		else if (request.id == JOIN_ROOM_REQUEST) {
			result = createRoom(request);
		}
		else {
			throw std::exception("Couldn't handle packet");
		}
		return result;
	}
	catch (nlohmann::json::exception& e)
	{
		ErrorResponse res = { "Invalid json in request" };
		return { JsonResponsePacketSerializer::serializeResponse(res), nullptr };
	}
	catch (std::exception& e)
	{
		ErrorResponse res = { e.what() };
		return { JsonResponsePacketSerializer::serializeResponse(res), nullptr };
	}

	ErrorResponse res = { "Invalid request" };
	return { JsonResponsePacketSerializer::serializeResponse(res), nullptr };
	return result;
}

MenuRequestHandler::MenuRequestHandler(std::string username, RoomManager rm, StatisticsManager ht,  RequestHandlerFactory* rhf) : m_users(username), m_roomManager(rm), m_statisticsManager(ht),  m_handlerFactory(rhf)
{
}

RequestResult MenuRequestHandler::signout(Request request)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::getRooms(Request request)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::getPlayersInRoom(Request request)
{
	GetPlayersInRoomRequest req = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(request.buffer.data(), request.buffer.size());
	std::vector<std::string> players;
	std::vector<LoggedUser> users = m_roomManager.getRoom(req.roomId).getAllUsers();
	for (auto it = users.begin(); it != users.end(); ++it)
	{
		players.push_back(it->getUsername());
	}
	GetPlayersInRoomResponse res = { GET_ROOMS_SUCCESS,  players };
	return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)m_handlerFactory->createMenuRequestHandler(m_users.getUsername()) };
}

RequestResult MenuRequestHandler::getHighscores(Request request)
{
	//Talk to yahav about. -> ask to change something to get user as well.
	vector<string> scores = m_statisticsManager.getHighScore();
	getHighScoreResponse res = { GET_HIGH_SCORE_SUCCESS };
	return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)m_handlerFactory->createMenuRequestHandler(m_users.getUsername()) };
}

RequestResult MenuRequestHandler::joinRoom(Request request)
{
	JoinRoomRequest req = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(request.buffer.data(), request.buffer.size());
	unsigned int status = m_roomManager.hasRoom(request.id) ? JOIN_ROOM_SUCCESS : REQUEST_ERROR;
	IRequestHandler* handler = nullptr;
	if (JOIN_ROOM_SUCCESS) {
		if (m_roomManager.getRoom(req.roomId).getRoomData().maxPlayers <= m_roomManager.getRoom(req.roomId).getAllUsers().size())
		{
			status = REQUEST_ERROR;
		}
		else
		{
			m_roomManager.getRoom(req.roomId).addUser(m_users);
			JoinRoomResponse res = { JOIN_ROOM_SUCCESS };
			return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)m_handlerFactory->createMenuRequestHandler(m_users.getUsername()) };
		}
	}
	
}

RequestResult MenuRequestHandler::createRoom(Request request)
{
	CreateRoomRequest req = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(request.buffer.data(), request.buffer.size());
	RoomData data = {
		0,
		req.roomName,
		req.maxUsers,
		req.answerTimeout,
		0
	};
	m_roomManager.createRoom(m_users, data);
	CreateRoomResponse res = { CREATE_ROOM_SUCCESS };
	return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)m_handlerFactory->createMenuRequestHandler(m_users.getUsername()) };
}
