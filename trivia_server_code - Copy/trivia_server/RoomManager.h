#pragma once
#include "Room.h"
#include <map>

class RoomManager
{
private:
	std::map<unsigned int, Room> m_rooms;
	std::mutex m_roomsMutex;
public:
	RoomManager();
	RoomManager(const RoomManager& rm);
	void createRoom(const LoggedUser firstUser, const RoomData roomInfo);
	void deleteRoom(unsigned int id);
	unsigned int getRoomState(unsigned int id);
	vector<RoomData> getAllRooms();
	Room getRoom(unsigned int roomId);
	bool hasRoom(unsigned int id);
};

