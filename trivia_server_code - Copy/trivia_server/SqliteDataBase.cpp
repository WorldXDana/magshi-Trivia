#include "SqliteDataBase.h"
#include <iostream>
#include "splite3.h"
#include <io.h>

#define QUESTION1 "INSERT INTO QUESTION(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4, ANSWER) VALUES('question1', 'answer1', 'answer2', 'answer3', 'answer4','answer');"
#define QUESTION2 "INSERT INTO QUESTION(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4, ANSWER) VALUES('question1', 'answer1', 'answer2', 'answer3', 'answer4','answer');"
#define QUESTION3 "INSERT INTO QUESTION(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4, ANSWER) VALUES('question1', 'answer1', 'answer2', 'answer3', 'answer4','answer');"
#define QUESTION4 "INSERT INTO QUESTION(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4, ANSWER) VALUES('question1', 'answer1', 'answer2', 'answer3', 'answer4','answer');"
#define QUESTION5 "INSERT INTO QUESTION(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4, ANSWER) VALUES('question1', 'answer1', 'answer2', 'answer3', 'answer4','answer');"
#define QUESTION6 "INSERT INTO QUESTION(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4, ANSWER) VALUES('question1', 'answer1', 'answer2', 'answer3', 'answer4','answer');"
#define QUESTION7 "INSERT INTO QUESTION(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4, ANSWER) VALUES('question1', 'answer1', 'answer2', 'answer3', 'answer4','answer');"
#define QUESTION8 "INSERT INTO QUESTION(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4, ANSWER) VALUES('question1', 'answer1', 'answer2', 'answer3', 'answer4','answer');"
#define QUESTION9 "INSERT INTO QUESTION(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4, ANSWER) VALUES('question1', 'answer1', 'answer2', 'answer3', 'answer4','answer');"
#define QUESTION10 "INSERT INTO QUESTION(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4, ANSWER) VALUES('question1', 'answer1', 'answer2', 'answer3', 'answer4','answer');"

int callbackUser(void* data, int argc, char** argv, char** azColName);
int callbackPassword(void* data, int argc, char** argv, char** azColName);
int callbackQuestion(void* data, int argc, char** argv, char** azColName);
int callbackaverageAnswerTime(void* data, int argc, char** argv, char** azColName);
int callbackNumPlayerGames(void* data, int argc, char** argv, char** azColName);
int callbackNumTotalAns(void* data, int argc, char** argv, char** azColName);
int callbackNumCorrectAns(void* data, int argc, char** argv, char** azColName);
int callbackTopThreeScores(void* data, int argc, char** argv, char** azColName);

using namespace std;
int COUNTER;
string COUNTERPASSWORDSTRING;

void SqliteDataBase::getSecurityKey(string str)
{
}

bool SqliteDataBase::open()
{
	string dbFileName = "db";
	int doesFileExist = _access(dbFileName.c_str(), 0); //The access function _ allows you to check whether a file exists and check whether the file has write permission.
	int res = sqlite3_open(dbFileName.c_str(), &this->DB);
	if (res != SQLITE_OK)
	{
		this->DB = nullptr;
		cout << "Failed to open DB" << endl;
		return false;
	};
	if (doesFileExist == -1) // not exists
	{
		create_Tabels();
		// init database
	}
}

void SqliteDataBase::close()
{
	sqlite3_close(this->DB);
	this->DB = nullptr;
}

void SqliteDataBase::create_Tabels()
{
	try {
		int check = 0;
		check = sqlite3_exec(this->DB, USERES.c_str(), nullptr, nullptr, nullptr);
		if (check != SQLITE_OK)
		{
			std::cout << "ERROR.. cant create USERES table\n";
		}
	}
	catch (std::exception& c)
	{
		std::cout << c.what() << '\n';
	}
	try {
		int check = 0;
		check = sqlite3_exec(this->DB, QUESTION.c_str(), nullptr, nullptr, nullptr);
		if (check != SQLITE_OK)
		{
			std::cout << "ERROR.. cant create QUESTION table\n";
		}
	}
	catch (std::exception& c)
	{
		std::cout << c.what() << '\n';
	}
	try {
		int check = 0;
		check = sqlite3_exec(this->DB, STATISTICS.c_str(), nullptr, nullptr, nullptr);
		if (check != SQLITE_OK)
		{
			std::cout << "ERROR.. cant create STATISTICS table\n";
		}
	}
	catch (std::exception& c)
	{
		std::cout << c.what() << '\n';
	}
	insertQuestion(QUESTION1);
	insertQuestion(QUESTION2);
	insertQuestion(QUESTION3);
	insertQuestion(QUESTION4);
	insertQuestion(QUESTION5);
	insertQuestion(QUESTION6);
	insertQuestion(QUESTION7);
	insertQuestion(QUESTION8);
	insertQuestion(QUESTION9);
	insertQuestion(QUESTION10);
}

void SqliteDataBase::insertQuestion(string str)
{
	int errPic = 0;
	try
	{
		errPic = sqlite3_exec(DB, str.c_str(), nullptr, nullptr, nullptr);
		if (errPic != SQLITE_OK)
		{
			cout << "Error with insertQuestion!\n" << endl;
		}
	}
	catch (exception& c)
	{
		cout << c.what() << '\n';
	}
}


bool SqliteDataBase::doesUserExist(const std::string& username)
{
	int getuSer = 0;
	string getuser = "SELECT * FROM USERS WHERE USER_NAME ='" + username + "';";

	try
	{
		getuSer = sqlite3_exec(DB, getuser.c_str(), callbackUser, nullptr, nullptr);
		if (getuSer != SQLITE_OK)
		{
			cout << "Error with doesUserExists!\n" << endl;

		}
		if (COUNTER == 0)
		{
			cout << "the user not exists! :( \n";
			return false;
		}
		else
		{
			cout << "the user exists! :) \n";
			return true;
		}
	}
	catch (exception& c)
	{
		cout << c.what() << '\n';
	}
}

bool SqliteDataBase::doesPasswordMatch(const std::string& username, const std::string& password)
{
	string passwordMatchString = "";
	string passwordMatch = "SELECT PASSWORD FROM USERS WHERE USER_NAME='" + username + "';";
	try
	{
		int check = sqlite3_exec(DB, passwordMatch.c_str(), callbackPassword, nullptr, nullptr);
		if (check != SQLITE_OK)
		{
			cout << "Error with doesPasswordMatch!\n" << endl;
		}
	}
	catch (exception& c)
	{
		cout << c.what();
	}
	if (COUNTERPASSWORDSTRING == password)
	{
		cout << "The password is match!!" << endl;
		return true;
	}
	else
	{
		cout << "The password is not match ):" << endl;
		return false;
	}
}

bool SqliteDataBase::addNewUser(const std::string& username, const std::string& password, const std::string& email)
{
	string userC = "INSERT INTO USERS(USER_NAME, PASSWORD, MAIL_ADDRESS) VALUES(\"" + username + "\", \"" + password + "\", \"" + email + "\");";
	try
	{
		int check = sqlite3_exec(DB, userC.c_str(), nullptr, nullptr, nullptr);
		if (check != SQLITE_OK)
		{
			cout << "Error with add new user!\n" << endl;
			return false;
		}
		else
		{
			return true;
		}
	}
	catch (exception& c)
	{
		cout << c.what();
	}
}

vector<string> SqliteDataBase::getTopThreeScores()
{
	string gettophigh = "SELECT USER_NAME, CAST(NUM_OF_CORRECT_ANSWERS AS float)/NUM_OF_TOTAL_ANSWERS * NUM_OF_GAMES / PLAYER_AVERAGE_ANSWER_TIME FROM STATISTICS;";
	vector<string>* topThreeScores = new vector<string>();
	try
	{
		int check = sqlite3_exec(DB, gettophigh.c_str(), callbackQuestion, topThreeScores, nullptr);
		if (check != SQLITE_OK)
		{
			cout << "Error with getTopThreeScores!\n" << endl;
		}
	}
	catch (exception& c)
	{
		cout << c.what();
	}
	return *topThreeScores;
}

int callbackTopThreeScores(void* data, int argc, char** argv, char** azColName)
{
	vector<string>* topThreeScores = (vector<string>*)data;
	topThreeScores->push_back(argv[0]);
	return 0;
}

vector<Question> SqliteDataBase::getQuestions(const int quantity) const
{
	string getquestion = "SELECT * FROM QUESTION";
	vector<Question>* newQuestion = new std::vector<Question>();

	try
	{
		int check = sqlite3_exec(DB, getquestion.c_str(), callbackQuestion, newQuestion, nullptr);
		if (check != SQLITE_OK)
		{
			cout << "Error with getQuestions!\n" << endl;
		}
	}
	catch (exception& c)
	{
		cout << c.what();
	}
	return *newQuestion;
}

float SqliteDataBase::getPlayerAverageAnswerTime(const std::string& username)
{
	string averageAnswerTimeastr = "SELECT PLAYER_AVERAGE_ANSWER_TIME FROM STATISTICS WHERE USER_NAME = '" + username + "';";
	float averageAnswerTime = 0;
	try
	{
		int check = sqlite3_exec(DB, averageAnswerTimeastr.c_str(), callbackNumCorrectAns, &averageAnswerTime, nullptr);
		if (check != SQLITE_OK)
		{
			cout << "Error with getPlayerAverageAnswerTime!\n" << endl;
		}
	}
	catch (exception& c)
	{
		cout << c.what();
	}
	return averageAnswerTime;
}

int callbackaverageAnswerTime(void* data, int argc, char** argv, char** azColName)
{
	float* counterofavarageanstime = (float*)data;
	for (int i = 0; i < argc; i++)
	{
		if (string(azColName[i]) == "PLAYER_AVERAGE_ANSWER_TIME")
		{
			*counterofavarageanstime = stof(argv[i]);
		}
	}
	return 0;
}

int SqliteDataBase::getNumOfCorrectAnswers(const std::string& username)
{
	string getNumOfCorrectAnswers1 = "SELECT NUM_OF_CORRECT_ANSWERS FROM STATISTICS WHERE USER_NAME = '" + username + "';";
	int countNumCorrectAns = 0;
	try
	{
		int check = sqlite3_exec(DB, getNumOfCorrectAnswers1.c_str(), callbackNumCorrectAns, &countNumCorrectAns, nullptr);
		if (check != SQLITE_OK)
		{
			cout << "Error with getNumOfCorrectAnswers!\n" << endl;
		}
	}
	catch (exception& c)
	{
		cout << c.what();
	}
	return countNumCorrectAns;
}

int callbackNumCorrectAns(void* data, int argc, char** argv, char** azColName)
{
	int* counterofcorrectanswer = (int*)data;
	for (int i = 0; i < argc; i++)
	{
		if (string(azColName[i]) == "NUM_OF_CORRECT_ANSWERS")
		{
			*counterofcorrectanswer = stoi(argv[i]);
		}
	}
	return 0;
}

int SqliteDataBase::getNumOfTotalAnswers(const std::string& username)
{
	string getNumOfTotalAns = "SELECT NUM_OF_TOTAL_ANSWERS FROM STATISTICS WHERE USER_NAME = '" + username + "';";
	int countNumTotalAns = 0;
	try
	{
		int check = sqlite3_exec(DB, getNumOfTotalAns.c_str(), callbackNumTotalAns, &countNumTotalAns, nullptr);
		if (check != SQLITE_OK)
		{
			cout << "Error with getNumOfTotalAnswers!\n" << endl;
		}
	}
	catch (exception& c)
	{
		cout << c.what();
	}
	return countNumTotalAns;
}

int callbackNumTotalAns(void* data, int argc, char** argv, char** azColName)
{
	int* countNumTotalAns = (int*)data;
	for (int i = 0; i < argc; i++)
	{
		if (string(azColName[i]) == "NUM_OF_CORRECT_ANSWERS")
		{
			*countNumTotalAns = stoi(argv[i]);
		}
	}
	return 0;
}

int SqliteDataBase::getNumOfPlayerGames(const std::string& username)
{
	string getNumOfPlayerGames = "SELECT NUM_OF_PLAYER_GAMES FROM STATISTICS WHERE USER_NAME = '" + username + "';";
	int countNumPlayerGames = 0;
	try
	{
		int check = sqlite3_exec(DB, getNumOfPlayerGames.c_str(), callbackNumPlayerGames, &countNumPlayerGames, nullptr);
		if (check != SQLITE_OK)
		{
			cout << "Error with getNumOfPlayerGames!\n" << endl;
		}
	}
	catch (exception& c)
	{
		cout << c.what();
	}
	return countNumPlayerGames;
}

int callbackNumPlayerGames(void* data, int argc, char** argv, char** azColName)
{
	int* counterofplayergame = (int*)data;
	for (int i = 0; i < argc; i++)
	{
		if (string(azColName[i]) == "NUM_OF_PLAYER_GAMES")
		{
			*counterofplayergame = stoi(argv[i]);
		}
	}
	return 0;
}


int callbackQuestion(void* data, int argc, char** argv, char** azColName)
{
	std::vector<Question>* new_vector = (std::vector<Question>*)data;
	Question newQuestion;
	for (int i = 0; i < argc; i++)
	{
		if (string(azColName[i]) == "ID")
		{
			newQuestion.setCorrectId(int(azColName[i]));
		}
		if (string(azColName[i]) == "ANSWER1")
		{
			newQuestion.addAnswer(azColName[i]);
		}
		if (string(azColName[i]) == "ANSWER2")
		{
			newQuestion.addAnswer(azColName[i]);
		}
		if (string(azColName[i]) == "ANSWER3")
		{
			newQuestion.addAnswer(azColName[i]);
		}
		if (string(azColName[i]) == "ANSWER4")
		{
			newQuestion.addAnswer(azColName[i]);
		}
	}
	new_vector->push_back(newQuestion);
	return 0;
}

int callbackUser(void* data, int argc, char** argv, char** azColName)
{
	int counter = 0;
	for (int i = 0; i < argc; i++)
	{
		if (string(azColName[i]) == "PASSWORD")
		{
			counter++;
		}
		if (string(azColName[i]) == "MAIL_ADDRESS")
		{
			counter++;
		}
		if (string(azColName[i]) == "USER_NAME")
		{
			counter++;
		}
	}
	COUNTER = counter;
	return 0;
}

int callbackPassword(void* data, int argc, char** argv, char** azColName)
{
	string counterPasswordString;
	for (int i = 0; i < argc; i++)
	{
		if (string(azColName[i]) == "PASSWORD")
		{
			counterPasswordString = argv[i];
		}
	}
	COUNTERPASSWORDSTRING = counterPasswordString;
	return 0;
}