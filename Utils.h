#pragma once
#include <string>
#include "Game.h"

const static int dirX[] = {1, 1, 0, -1, -1, -1, 0, 1};
const static int dirY[] = {0, 1, 1, 1, 0, -1, -1, -1};
const static int MAX_X = 200;
const static int MAX_Y = 200;
const static int OFFSET = 50;

int promptUser(const std::string& message, int mn, int mx);
int randomIntegerFromInterval(int mn, int mx);
void initializeFont(sf::Font& font);
std::vector<int> generateRandomArray(int size, int mn, int mx);
std::string getPercentage(int newStat, int oldStat);
void checkCoordinates(int x, int y);
void checkCoordinates(int pos);
sf::Color colorMixer(const sf::Color &color1, const sf::Color &color2);