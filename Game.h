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
    virtual ~Game();
    friend std::ostream &operator<<(std::ostream &os, const Game &game);
    friend class Food;
    friend class Individual;

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
    void draw(sf::Drawable &drawable);
};