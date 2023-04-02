#pragma once
#include <string>
#include "Game.h"

const int dirX[8] = {1, 1, 0, -1, -1, -1, 0, 1};
const int dirY[8] = {0, 1, 1, 1, 0, -1, -1, -1};

const int MAX_X = 1000;
const int MAX_Y = 1000;

int promptUser(const std::string& message, int mn, int mx);
int randomIntegerFromInterval(int mn, int mx);