#include <vector>
#include "requestAndRespond.h"
#include "json.hpp"

//
using namespace nlohmann;

class JsonResponsePacketSerializer
{
public:
	static std::vector<char> serializeResponse(ErrorResponse response);
	static std::vector<char> serializeResponse(LoginResponse response);
	static std::vector<char> serializeResponse(SignupResponse response);

	static std::vector<char> serializeResponse(LogoutResponse response);
	static std::vector<char> serializeResponse(GetRoomsResponse response);
	static std::vector<char> serializeResponse(GetPlayersInRoomResponse response);
	static std::vector<char> serializeResponse(JoinRoomResponse response);
	static std::vector<char> serializeResponse(CreateRoomResponse response);
	static std::vector<char> serializeResponse(getHighScoreResponse response);
	static std::vector<char> serializeResponse(getPersonalStatsResponse response);
private:
	static std::vector<char> jsonToPacket(int code, std::string data);
	static std::vector<char> intToBytes(int number);
};