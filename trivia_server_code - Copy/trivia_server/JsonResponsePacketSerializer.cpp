#include "JsonResponsePacketSerializer.h"

//returns them in a form of vector --> an ErrorResponse.
std::vector<char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse response)
{
	json jsonData = {
		{"message", response.message}
	};
	return jsonToPacket(REQUEST_ERROR, jsonData.dump());
}

//returns them in a form of vector --> an LoginResponse.
std::vector<char> JsonResponsePacketSerializer::serializeResponse(LoginResponse response)
{
	json jsonData = {
		{"status", response.status}
	};
	return jsonToPacket(response.status, jsonData.dump());
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(SignupResponse response)
{
	json jsonData = {
		{"status", response.status}
	};
	return jsonToPacket(response.status, jsonData.dump());
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(LogoutResponse response)
{
	json jsonData = {
		{"status", response.status}
	};
	return jsonToPacket(response.status, jsonData.dump());
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse response)
{
	json jsonData = {
		{"status", response.status},
		{"rooms", {}}
	};

	for (auto it = response.rooms.begin(); it != response.rooms.end(); ++it) {
		jsonData["rooms"].push_back({
			{"id", it->id},
			{"name", it->name},
			{"maxPlayers", it->maxPlayers},
			{"timePerQuestion", it->timePerQuestion},
			{"isActive", it->isActive},

			});
	}
	return jsonToPacket(response.status, jsonData.dump());
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse response)
{
	json jsonData = {
			{"status", response.status},
			{"players", response.players}
	};
	return jsonToPacket(response.status, jsonData.dump());
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse response)
{
	json jsonData = {
		{"status", response.status}
	};
	return jsonToPacket(response.status, jsonData.dump());
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse response)
{
	json jsonData = {
		{"status", response.status}
	};
	return jsonToPacket(response.status, jsonData.dump());
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(getHighScoreResponse response)
{
	json jsonData = {
	{"status", response.status},
	{"highscores", {}}
	};

	for (auto it = response.highscores.begin(); it != response.highscores.end(); ++it)
	{
		jsonData["highscores"].push_back({
			{"username", it->username},
			{"score", it->score}
			});
	}

	return jsonToPacket(response.status, jsonData.dump());
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(getPersonalStatsResponse response)
{
	json jsonData = {
	{"status", response.status},
	{"statistics", {}}
	};

	for (auto it = response.statistics.begin(); it != response.statistics.end(); ++it)
	{
		jsonData["statistics"].push_back({
			{"username", it->username},
			{"score", it->score}
			});
	}

	return jsonToPacket(response.status, jsonData.dump());
}

std::vector<char> JsonResponsePacketSerializer::jsonToPacket(int code, std::string data)
{
	std::vector<char> packetBytes;
	packetBytes.push_back(static_cast<unsigned char>(code));
	std::vector<char> dataLengthBytes = intToBytes(data.size() + 1);
	std::copy(dataLengthBytes.begin(), dataLengthBytes.end(), std::back_inserter(packetBytes));
	std::copy(data.begin(), data.end(), std::back_inserter(packetBytes));

	return packetBytes;
}

std::vector<char> JsonResponsePacketSerializer::intToBytes(int number)
{
	std::vector<char> arrayOfBytes(4);
	for (int i = 0; i < 4; i++)
	{
		arrayOfBytes[3 - i] = (number >> (i * 8));
	}
	return arrayOfBytes;
}

