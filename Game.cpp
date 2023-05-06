#include <iostream>
#include "Game.h"
#include "Food.h"
#include "Individual.h"
#include "Cell.h"
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
    displayMatrix.clear();
    displayMatrix.resize(width * height * Cell::CELL_SIZE * Cell::CELL_SIZE);
    for (int i = 0; i < width * height; i++) {
        if (board[i] != nullptr) {
            updateDisplayMatrix(i);
            auto* individual = dynamic_cast<Individual*>(board[i]);
            if (individual != nullptr) {
                individual->move();
                int coords = findFoodInRange(individual, Individual::VISION);
                if (coords != -1) {
                    auto* food = dynamic_cast<Food*>(board[coords]);
                    if (food != nullptr) {
                        futureBoard[coords] = individual;
                    }
                }
                futureBoard[individual->getPosition()] = individual;
            } else {
                futureBoard[i] = board[i];
            }
        }
    }
    window.draw(&displayMatrix[0], displayMatrix.size(), sf::Points);
    window.display();
    board = futureBoard;
    futureBoard.clear();
    futureBoard.resize(width * height);
}

Game::Game() : width(MAX_X),
               height(MAX_Y),
               numberOfIndividuals(promptUser("Specify the desired number of individuals", 10, 1000)),
               quantityOfFood(promptUser("Specify the desired quantity of food", 10, 1500)) {
    window.create(sf::VideoMode(width * Cell::CELL_SIZE, height * Cell::CELL_SIZE), "Game of Life");
    initializeFont(font);
    board.resize(width * height);
    futureBoard.resize(width * height);
    generateCreatures();
    initializeDisplay();
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(15);
}

void Game::generateCreatures() {
    auto randomPositions = generateRandomArray(numberOfIndividuals + quantityOfFood, 0, width * height);
    for (int i = 0; i < numberOfIndividuals; i++) {
        Cell *individual = new Individual(randomPositions[i] / height, randomPositions[i] % height);
        board[randomPositions[i]] = individual;
    }
    for (int i = numberOfIndividuals; i < numberOfIndividuals + quantityOfFood; i++) {
        Cell *food = new Food(randomPositions[i] / height, randomPositions[i] % height);
        board[randomPositions[i]] = food;
    }
}

Game::~Game() {
    std::cout << "Destructor called\n";
}

std::ostream &operator<<(std::ostream &os, const Game &game) {
    os << " width: " << game.width << " height: " << game.height << " numberOfIndividuals: "
       << game.numberOfIndividuals << " quantityOfFood: " << game.quantityOfFood;
    return os;
}

void Game::initializeDisplay() {
    displayMatrix.resize(width * height * Cell::CELL_SIZE * Cell::CELL_SIZE);
    for (int i = 0; i < height * Cell::CELL_SIZE; ++i) {
        for (int j = 0; j < width * Cell::CELL_SIZE; ++j) {
            displayMatrix[i * width * Cell::CELL_SIZE + j] = sf::Vertex(sf::Vector2f(j, i), sf::Color::Black);
        }
    }
}

void Game::updateDisplayMatrix(int i, sf::Color color) {
    int x = i / height;
    int y = i % height;
    for (int j = 0; j < Cell::CELL_SIZE; ++j) {
        for (int k = 0; k < Cell::CELL_SIZE; ++k) {
            displayMatrix[(x * Cell::CELL_SIZE + j) * width * Cell::CELL_SIZE + y * Cell::CELL_SIZE + k] =
                    sf::Vertex(sf::Vector2f(y * Cell::CELL_SIZE + k, x * Cell::CELL_SIZE + j), color);
        }
    }
}

void Game::updateDisplayMatrix(int i) {
    updateDisplayMatrix(i, board[i]->getColor());
}

int Game::findFoodInRange(Individual *individual, int radius) {
    int position = individual->getPosition();
    int x = position / height;
    int y = position % height;
    // check in the circle centered at (x, y) with radius i
    for (int j = x - radius; j <= x + radius; ++j) {
        for (int k = y - radius; k <= y + radius; ++k) {
            int newPos = j * height + k;
            if (newPos >= 0 && newPos < width * height && board[newPos] != nullptr) {
                auto* food = dynamic_cast<Food*>(board[newPos]);
                if (food != nullptr) {
                    return newPos;
                }
            }
        }
    }
    return -1;
}
