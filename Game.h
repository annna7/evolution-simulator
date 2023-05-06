#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <set>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <utility>
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
    std::vector<Cell*> board;
    std::vector<Cell*> futureBoard;

    std::vector<sf::Vertex> displayMatrix;

    int width;
    int height;
    int numberOfIndividuals;
    int quantityOfFood;
    sf::Font font;
    sf::RenderWindow window;
    Game();
    void generateCreatures();
    void display();
    void initializeDisplay();

    void updateDisplayMatrix(int i);
};