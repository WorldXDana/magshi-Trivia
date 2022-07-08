#include "Question.h"

string Question::getTheQuestion()
{
    return this->m_question;
}

vector<string> Question::getPossibleAnswers()
{
    return this->m_possibleAnswers;
}

void Question::set_possibleAnswers(std::vector<string> possibleAnswers)
{
    this->m_possibleAnswers = possibleAnswers;
}

int Question::getCorrectAnsId()
{
    return this->m_CorrectId;
}

void Question::setCorrectId(int id)
{
    this->m_CorrectId = id;
}

string Question::getTheCorrectAnswer()
{
    return string();
}

void Question::setTheQuestion(string question)
{
    this->m_question = question;
}

void Question::addAnswer(string answer)
{
    this->m_possibleAnswers.push_back(answer);
}

bool Question::operator==(const Question& q) const
{
    return this->m_question == q.m_question;
}
