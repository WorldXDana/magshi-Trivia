#include "RoomManager.h"


RoomManager::RoomManager()
{
}

RoomManager::RoomManager(const RoomManager& rm):
	m_rooms(rm.m_rooms)
{
}

void RoomManager::createRoom(const LoggedUser firstUser, RoomData roomInfo)
{
	Room newRoom(roomInfo);
	newRoom.addUser(firstUser);
	int num = roomInfo.id;
	std::lock_guard<std::mutex> locker(m_roomsMutex);
	this->m_rooms.insert(std::pair<unsigned int, Room>(newRoom.getRoomData().id, newRoom));

}

void RoomManager::deleteRoom(unsigned int id)
{
	std::lock_guard<std::mutex> locker(m_roomsMutex);
	this->m_rooms.erase(id);
}

unsigned int RoomManager::getRoomState(unsigned int id)
{
	return m_rooms.find(id)->second.getRoomData().isActive;
}

vector<RoomData> RoomManager::getAllRooms()
{
	std::vector<RoomData> roomsData;
	for (auto it = m_rooms.begin(); it != m_rooms.end(); ++it) {
		roomsData.push_back((it->second).getRoomData());
	}
	return roomsData;
}

Room RoomManager::getRoom(unsigned int roomId)
{
	if (m_rooms.find(roomId) == m_rooms.end())
	{
		throw std::runtime_error("Room with id " + std::to_string(roomId) + " doesn't exist");
	}
	return m_rooms.find(roomId)->second;
}

bool RoomManager::hasRoom(unsigned int id)
{
	return m_rooms.find(id) != m_rooms.end();
}
