#include "saveScore.hpp"

void addScore(int score)
{
    std::ifstream file("scores.txt");
    if (file.is_open())
    {
        std::vector<int> scores;
        int              currentScore = 0;
        while (file >> currentScore)
        {
            scores.push_back(currentScore);
        }
        scores.push_back(score);
        file.close();

        std::sort(scores.begin(), scores.end(), std::greater<int>());

        std::ofstream outFile("scores.txt");
        if (outFile.is_open())
        {
            for (int score : scores)
            {
                outFile << score << std::endl;
            }
            outFile.close();
        }
        else
        {
            std::cout << "Unable to open the file." << std::endl;
        }
    }
    else
    {
        std::cout << "Unable to open the file." << std::endl;
    }
}

void displayScores(p6::Context& ctx)
{
    std::ifstream file("scores.txt", std::ios::in);
    if (file.is_open())
    {
        std::vector<int> scores;
        int              score = 0;
        while (file >> score)
        {
            scores.push_back(score);
        }
        file.close();
        int it = 0;
        if (!scores.empty())
        {
            for (int score : scores)
            {
                printHighScores(ctx, score, it);
                it++;
                if (it > 5)
                    break;
            }
        }
        else
        {
            std::cout << "No scores recorded yet." << std::endl;
        }
    }
    else
    {
        std::cout << "Unable to open the file." << std::endl;
    }
}
