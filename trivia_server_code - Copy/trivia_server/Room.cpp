#include "Room.h"

Room::Room(RoomData newRoom) : m_metaData(newRoom)
{

}

Room::Room(const Room& other)
{
	*this = other;
}

Room::~Room()
{
	
}

void Room::addUser(LoggedUser newUser)
{
	std::lock_guard<std::mutex> locker(m_UsersMutex);
	this->m_users.push_back(newUser);
}

void Room::removeUser(LoggedUser removedUser)
{
	std::lock_guard<std::mutex> locker(m_UsersMutex);
	remove(this->m_users.begin(), this->m_users.end(), removedUser);
}

vector<LoggedUser> Room::getAllUsers()
{
	return std::vector<LoggedUser>(m_users);
}

RoomData Room::getRoomData()
{
	return this->m_metaData;
}

Room& Room::operator=(const Room& other)
{
	Room temp;
	temp.m_users = other.m_users;
	//temp.m_UsersMutex = other.m_UsersMutex;
	temp.m_metaData = other.m_metaData;
	return temp;
}
