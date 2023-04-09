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

class Game {
public:
    static Game &getInstance();
    void run();
    Game(const Game &other) = delete;
    Game& operator=(const Game &other) = delete;
    ~Game();
    friend std::ostream &operator<<(std::ostream &os, const Game &game);
    void draw(sf::Drawable &drawable);

private:
    int** board;
    int width;
    int height;
    int numberOfIndividuals;
    int quantityOfFood;
    sf::Font font;
    sf::RenderWindow window;
    std::vector<Individual> individuals;
    std::vector<Food>foods;
    Game();
    void display();
    void generateIndividuals();
    void drawIndividuals();
    void updateIndividuals();
    void generateFood();
    void drawFood();
};