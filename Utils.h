#pragma once
#include <string>
#include <array>
#include "Game.h"

const static int dirX[] = {1, 1, 0, -1, -1, -1, 0, 1};
const static int dirY[] = {0, 1, 1, 1, 0, -1, -1, -1};
const static int MAX_X = 200;
const static int MAX_Y = 200;

int promptUser(const std::string& message, int mn, int mx);
int randomIntegerFromInterval(int mn, int mx);
void initializeFont(sf::Font& font);
std::vector<int> generateRandomArray(int size, int mn, int mx);
long long getCurrentTime();
std::string getPercentage(int newStat, int oldStat);

const static int RED_BULL = 1;