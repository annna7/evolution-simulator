#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <set>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <memory>
#include "Individual.h"
#include "Utils.h"
#include "Food.h"
#include "Cell.h"

class Game {
public:
    static Game &getInstance();
    void run();
    Game(const Game &other) = delete;
    Game& operator=(const Game &other) = delete;
    ~Game();
    friend std::ostream &operator<<(std::ostream &os, const Game &game);

private:
    std::unordered_map<int, std::pair<int, int>> fitnessMap;
    std::vector<std::shared_ptr<Cell>> board;
    std::vector<std::shared_ptr<Cell>> futureBoard;
    std::vector<sf::Vertex> displayMatrix;

    int width;
    int height;
    int keystoneNumber, clairvoyantNumber, redBullNumber;
    int quantityOfFood;

    sf::Clock clock;
    sf::Font font;
    sf::RenderWindow window;

    Game();
    void generateCells();
    void display();
    void initializeDisplay();
    void updateDisplayMatrix(int i);
    void updateDisplayMatrix(int i, sf::Color color);
    bool isPaused = false;
    int epochCounter = 0;
    static const int EPOCH_DURATION = 2000;
    static const int BOTTOM_BAR_HEIGHT = 100;
    void endEpoch();
    void menuDisplay();
    void computeFitness();
    const static std::unordered_map<int, std::string> raceDict;
    void showStatistics();
    int findFreeSpot(const std::shared_ptr<Individual>&, int radius);
    int findFoodInRange(const std::shared_ptr<Individual>&, int radius);

    std::unordered_map<int, int> computeNewGeneration();
    void resetGeneration(std::unordered_map<int, int> generation);
    void resetBoard();

    int getTotalSurvivalRate();
};
