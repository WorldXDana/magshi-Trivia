#pragma once
#include <string>
#include "Room.h"
#include <vector>
//#include "IRequestHandler.h"

class IRequestHandler;

//Basic data structures.
typedef struct Highscore {
	std::string username; 
	int score;
} Highscore;

typedef enum RequestID {
	LOGIN_REQUEST = 100,
	SIGNUP_REQUEST = 200,
	LOGOUT_REQUEST = 300,
	GET_ROOMS_REQUEST = 400,
	GET_PLAYERS_IN_ROOM_REQUEST = 500,
	JOIN_ROOM_REQUEST = 600,
	CREATE_ROOM_REQUEST = 700,
	GET_HIGH_SCORE_REQUEST = 800,
	GET_PERSONAL_STATS_REQUEST = 900,
} RequestID;

typedef enum ResponseID {
	REQUEST_ERROR = 201,
	LOGIN_SUCCESS = 202,
	SIGNUP_SUCCESS = 203,
	LOGOUT_SUCCESS = 204,
	GET_ROOMS_SUCCESS = 205,
	GET_PLAYERS_IN_ROOM_SUCCESS = 206,
	JOIN_ROOM_SUCCESS = 207,
	CREATE_ROOM_SUCCESS = 208,
	GET_HIGH_SCORE_SUCCESS = 209,
	GET_PERSONAL_STATS_SUCCSES = 210,
} ResponseID;

typedef struct getPersonalStatsResponse {
	ResponseID status;
	vector<Highscore> statistics;
} getPersonalStatsResponse;

typedef struct getHighScoreResponse {
	ResponseID status;
	vector<Highscore> highscores;
} getHighScoreResponse;

typedef struct CreateRoomResponse {
	ResponseID status;
} CreateRoomResponse;

typedef struct JoinRoomResponse {
	ResponseID status;
} JoinRoomResponse;

typedef struct GetPlayersInRoomResponse {
	ResponseID status;
	vector<string> players;
} GetPlayersInRoomResponse;

typedef struct GetRoomsResponse {
	ResponseID status;
	vector<RoomData> rooms;
} GetRoomsResponse;

typedef struct LoginResponse {
	ResponseID status;
} LoginResponse;

typedef struct SignupResponse {
	ResponseID status;
} SignupResponse;

typedef struct LogoutResponse {
	ResponseID status;
} LogoutResponse;

typedef struct ErrorResponse {
	std::string message;
} ErrorResponse;

typedef struct Request {
	int id;
	time_t requestTime;
	std::vector<char> buffer;
} Request;

typedef struct CreateRoomRequest {
	string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
} CreateRoomRequest;

typedef struct GetPlayersInRoomRequest {
	unsigned int roomId;
} GetPlayersInRoomRequest;

typedef struct JoinRoomRequest {
	unsigned int roomId;
} JoinRoomRequest;

typedef struct RequestResult {
	std::vector<char> response;
	IRequestHandler* newHandler;
} RequestResult;

typedef struct LoginRequest {
	std::string username;
	std::string password;
} LoginRequest;

typedef struct SignupRequest {
	std::string username;
	std::string password;
	std::string email;
} SignupRequest;


