#include <iostream>
#include "Game.h"
#include "Food.h"
#include "Individual.h"
#include <SFML/Graphics.hpp>
#include <chrono>

Game &Game::getInstance() {
    static Game instance;
    return instance;
}

void Game::run() {
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        display();
    }
}


void Game::display() {
    window.clear();
    auto nowTime = std::chrono::high_resolution_clock::now();
    auto nowMS = std::chrono::time_point_cast<std::chrono::milliseconds>(nowTime);
    auto nowValue = nowMS.time_since_epoch().count();
    sf::Text message(" EVOLUTION SIMULATOR                      " + std::to_string(nowValue), font);
    window.draw(message);
    drawIndividuals();
    updateIndividuals();
    drawFood();
    window.display();
}

Game::Game() : width(MAX_X),
               height(MAX_Y),
               numberOfIndividuals(promptUser("Specify the desired number of individuals", 10, 1000)),
               quantityOfFood(promptUser("Specify the desired quantity of food", 10, 1500)) {
    board = new int*[height];
    for (int i = 0; i < height; ++i) {
        board[i] = new int[width];
    }
    std::cout << "Game created" << std::endl;
    window.create(sf::VideoMode(width, height), "Game of Life");
    font.loadFromFile("RobotoMono-Regular.ttf");
    generateIndividuals();
    generateFood();
}


void Game::generateIndividuals() {
    for (int i = 0; i < numberOfIndividuals; i++) {
        Individual individual = Individual();
        individuals.push_back(individual);
    }
}

void Game::generateFood() {
    for (int i = 0; i < quantityOfFood; i++) {
        Food food = Food();
        foods.push_back(food);
    }
}


void Game::drawIndividuals() {
    for (int i = 0; i < numberOfIndividuals; i++) {
        individuals[i].draw();
    }
}

void Game::draw(sf::Drawable &drawable) {
    window.draw(drawable);
}

void Game::updateIndividuals() {
    for (int i = 0; i < numberOfIndividuals; i++) {
        individuals[i].move();
        individuals[i].update_life_time(-1);
    }
}

void Game::drawFood() {
    for (int i = 0; i < quantityOfFood; i++) {
        foods[i].draw();
    }
}


Game::~Game() {
    std :: cout << "Destructor called\n";
    for (int i = 0 ; i < height; ++i) {
        delete[] board[i];
    }
    delete[] board;
}

std::ostream &operator<<(std::ostream &os, const Game &game) {
    os << "board: " << game.board << " width: " << game.width << " height: " << game.height << " numberOfIndividuals: "
       << game.numberOfIndividuals << " quantityOfFood: " << game.quantityOfFood;
    return os;
}

