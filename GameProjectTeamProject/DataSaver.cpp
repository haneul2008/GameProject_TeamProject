#include<fstream>
#include "DataSaver.h"

const int DataSaver::GetBestScore() const
{
	int result = 0;
    std::ifstream mapFile("Data.txt");
    if (mapFile.is_open())
    {
        mapFile >> result;
        mapFile.close();
    }

    return result;
}

void DataSaver::SetBestScore(const int& score)
{
	int bestScore = GetBestScore();

    if (score <= bestScore) return;

	std::ofstream saveFile("Data.txt");

    if(saveFile.is_open())
    {
        saveFile << score;
        saveFile.close();
    }
}
