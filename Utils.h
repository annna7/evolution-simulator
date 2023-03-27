#pragma once
#include <string>
#include "Game.h"

int promptUser(const std::string& message, int mn, int mx);
int randomIntegerFromInterval(int mn, int mx);
const int dirX[8] = {1, 1, 0, -1, -1, -1, 0, 1};
const int dirY[8] = {0, 1, 1, 1, 0, -1, -1, -1};

const int MIN_X = 0;
const int MIN_Y = 0;
const int MAX_X = 500;
const int MAX_Y = 500;
