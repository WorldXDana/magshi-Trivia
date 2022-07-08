#include "JsonRequestPacketDeserializer.h"
#include <iostream>

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(char* buffer, int len)
{
	std::string data(buffer, len - 1);
	json jsonData = json::parse(data);
	return LoginRequest({ jsonData["username"], jsonData["password"] });
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(char* buffer, int len)
{
	std::string data(buffer, len - 1);
	json jsonData = json::parse(data);
	return SignupRequest({ jsonData["username"], jsonData["password"], jsonData["email"] });
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(char* buffer, int len)
{
	std::string data(buffer, len - 1);
	json jsonData = json::parse(data);
	return GetPlayersInRoomRequest({ jsonData["roomId"] });
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(char* buffer, int len)
{
	std::string data(buffer, len - 1);
	json jsonData = json::parse(data);
	return CreateRoomRequest({ jsonData["roomName"], jsonData["maxUsers"], jsonData["questionCount"], jsonData["answerTimeout"] });
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(char* buffer, int len)
{
	std::string data(buffer, len - 1);
	json jsonData = json::parse(data);
	return JoinRoomRequest({ jsonData["roomId"] });
}
