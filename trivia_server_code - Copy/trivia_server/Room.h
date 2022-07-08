#pragma once
#include "LoginManager.h"
#include <mutex>

class LoginManager;

typedef struct RoomData {
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfMaxQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
} RoomData;


class Room
{
public:
	Room() = default;
	Room(RoomData newRoom);
	Room(const Room &other);
	~Room();

	void addUser(LoggedUser newUser);
	void removeUser(LoggedUser removedUser);
	vector<LoggedUser> getAllUsers();
	RoomData getRoomData();

	Room& operator=(const Room& other);
private:
	RoomData m_metaData;
	vector<LoggedUser> m_users;
	std::mutex m_UsersMutex;
};