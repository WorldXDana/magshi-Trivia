#pragma once
#include <string>
#include <vector>
using namespace std;
class Question
{

public:
	Question(string question, vector<string> answers, int correctId) {};
	Question() {};
	~Question() {};

	string getTheQuestion();
	void setTheQuestion(string question);

	vector<string> getPossibleAnswers();
	void set_possibleAnswers(std::vector<string> possibleAnswers);

	int getCorrectAnsId();
	void setCorrectId(int id);

	string getTheCorrectAnswer();

	void addAnswer(string answer);

	bool operator==(const Question& q) const;
	
private:
	string m_question;
	vector<string> m_possibleAnswers;
	int m_CorrectId;

};
