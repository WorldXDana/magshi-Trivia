#pragma once
#include "IDatabase.h"
#include <vector>
class StatisticsManager
{
public:
	StatisticsManager();
	StatisticsManager(IDatabase* db);
	vector<string> getHighScore();
	vector<string> getUserStatistics(string username);

private:
	IDatabase* m_database;
};

