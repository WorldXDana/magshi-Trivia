#pragma once
#include <vector>
#include <string>
#include "splite3.h"
#include "IDatabase.h"
#include "Question.h"
using namespace std;

const string USERES = "CREATE TABLE USERS (USER_NAME TEXT PRIMARY KEY NOT NULL, PASSWORD TEXT NOT NULL, MAIL_ADDRESS TEXT NOT NULL);";
const string QUESTION = "CREATE TABLE QUESTION(ID INTEGER NULL, QUESTION TEXT NOT NULL, ANSWER1 TEXT NOT NULL, ANSWER2 TEXT NOT NULL, ANSWER3 TEXT NOT NULL, ANSWER4 TEXT NOT NULL, ANSWER TEXT NOT NULL);";
const string STATISTICS = "CREATE TABLE STATISTICS(USER_NAME TEXT PRIMARY KEY NOT NULL, PLAYER_AVERAGE_ANSWER_TIME REAL NOT NULL, NUM_OF_CORRECT_ANSWERS INTEGER NOT NULL, NUM_OF_TOTAL_ANSWERS INTEGER NOT NULL, NUM_OF_PLAYER_GAMES INTEGER NOT NULL, NUM_OF_GAMES INTEGER NOT NULL);";

class SqliteDataBase : public IDatabase
{
public:
	SqliteDataBase() = default;
	virtual ~SqliteDataBase() = default;
	
	bool doesUserExist(const std::string& username) override;
	bool doesPasswordMatch(const std::string& username, const std::string& password) override;
	bool addNewUser(const std::string& username, const std::string& password, const std::string& email) override;
	vector<Question> getQuestions(const int quantity) const;
	float getPlayerAverageAnswerTime(const std::string& username) override;
	int getNumOfCorrectAnswers(const std::string& username) override;
	int getNumOfTotalAnswers(const std::string& username) override;
	int getNumOfPlayerGames(const std::string& username) override;
	void getSecurityKey(string str) override;
	bool open();
	void close();
	void create_Tabels();

	void insertQuestion(string str);
	vector<string> getTopThreeScores() override;

private:
	sqlite3* DB;
};

