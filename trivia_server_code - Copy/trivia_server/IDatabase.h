#pragma once
#include <string>
#include <vector>
using namespace std;
class IDatabase
{
public:
	
	//IDatabase(const IDatabase&) = default;
	virtual ~IDatabase() = default;
	virtual bool doesUserExist(const string &username) = 0;
	virtual bool doesPasswordMatch(const string & username, const string & password) = 0;
	virtual bool addNewUser(const string& username, const string& password, const string& email) = 0;
	//virtual std::vector<Question> getQuestions(const int quantity) = 0;
	virtual float getPlayerAverageAnswerTime(const string &username) = 0;
	virtual int getNumOfCorrectAnswers(const string &username) = 0;
	virtual int getNumOfTotalAnswers(const string &username) = 0;
	virtual int getNumOfPlayerGames(const string &username) = 0;
	virtual vector<string> getTopThreeScores() = 0;
	virtual void getSecurityKey(string str) = 0;
};