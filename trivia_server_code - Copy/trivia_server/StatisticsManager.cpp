#include "StatisticsManager.h"

StatisticsManager::StatisticsManager()
{
}

StatisticsManager::StatisticsManager(IDatabase* db)
{
	this->m_database = db;
}

vector<string> StatisticsManager::getHighScore()
{
	return this->m_database->getTopThreeScores();
}

vector<string> StatisticsManager::getUserStatistics(string username)
{
	vector<string> statistics;
	statistics.push_back(to_string(this->m_database->getPlayerAverageAnswerTime(username)));
	statistics.push_back(to_string(this->m_database->getNumOfCorrectAnswers(username)));
	statistics.push_back(to_string(this->m_database->getNumOfTotalAnswers(username)));
	statistics.push_back(to_string(this->m_database->getNumOfPlayerGames(username)));
	return statistics;
}
