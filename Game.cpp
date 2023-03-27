#include <iostream>
#include "Game.h"
#include "Utils.h"
#include "Food.h"
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
    sf::Text message("Hello, World !" + std::to_string(nowValue), font);
    window.draw(message);
    drawIndividuals();
    updateIndividuals();
    drawFood();
    window.display();
}


//Game::Game() : width(promptUser("Specify the desired window width", 100, 1000)),
//                height(promptUser("Specify the desired window width", 10, 1000)),
//                numberOfCells(promptUser("Specify the desired window width", 10, 500)) {
//    std::cout << "Game created" << std::endl;
//    window.create(sf::VideoMode(width, height), "Game of Life");
//    font.loadFromFile("RobotoMono-Regular.ttf");
//}


Game::Game(): width(500),
               height(500),
               numberOfIndividuals(1000),
               quantityOfFood(100)
               {
    board = new int*[height];
    for (int i = 0; i < height; ++i) {
        board[i] = new int[width];
    }
    srand(time(nullptr));
    std::cout << "Game created" << std::endl;
    window.create(sf::VideoMode(width, height), "Game of Life");
    font.loadFromFile("RobotoMono-Regular.ttf");
    generateIndividuals();
    generateFood();
}

int Game::getHeight() const {
    return Game::getInstance().height;
}

int Game::getWidth() const {
    return Game::getInstance().width;
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

void Game::printIndividuals() {
    for (int i = 0; i < numberOfIndividuals; i++) {
        std::cout << individuals[i] << std::endl;
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

void Game::printFood() {
    for (int i = 0; i < quantityOfFood; i++) {
        std::cout << foods[i] << std::endl;
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
