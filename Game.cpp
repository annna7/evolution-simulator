#include <iostream>
#include "Game.h"
#include "Food.h"
#include "Individual.h"
#include "Cell.h"
#include "RedBull.h"
#include "Keystone.h"
#include "Clairvoyant.h"
#include <SFML/Graphics.hpp>

const std::unordered_map<int, std::string> Game::raceDict = {
        {RED_BULL, "RedBull"},
        {KEY_STONE, "Keystone"},
        {CLAIRVOYANT, "Clairvoyant"}
};

Game &Game::getInstance() {
    static Game instance;
    return instance;
}

void Game::computeFitness() {
    for (auto &cell : board) {
        if (cell != nullptr) {
            // check if the cell has the same type as individual
            // for instance, if I pass a Redbull, check if the cell is a Redbull
            auto *individualCell = dynamic_cast<Individual *>(cell);
            if (individualCell != nullptr) {
                fitnessCache[individualCell->getType()].first += 1;
                if (!individualCell->checkIfAlive()) {
                    board[individualCell->getPosition()] = nullptr;
                } else {
                    fitnessCache[individualCell->getType()].second += 1;
                }
            }
        }
    }

    for (int i = 0; i < width * height; ++i) {
        updateDisplayMatrix(i);
    }

    window.clear();
    window.draw(&displayMatrix[0], displayMatrix.size(), sf::Points);
    window.display();
}

void Game::endEpoch() {
    epochCounter++;
}

void Game::menuDisplay() {
    sf::Text message = sf::Text("Epoch: " + std::to_string(epochCounter) + " has ended! Press SPACE to continue.", font);
    message.setPosition(70, height * Cell::CELL_SIZE);
    message.setCharacterSize(15);
    window.draw(message);
}

void Game::run() {
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        menuDisplay();
        if (!isPaused) {
            if ((getCurrentTime() - initialTime) >= EPOCH_DURATION) {
                endEpoch();
                computeFitness();
                showStatistics();
                isPaused = true;
            } else {
                display();
            }
        } else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                isPaused = false;
                initialTime = getCurrentTime();
            }
        }
        window.display();
    }
}


void Game::display() {
    window.clear();
    displayMatrix.clear();
    displayMatrix.resize(width * height * Cell::CELL_SIZE * Cell::CELL_SIZE);
    for (int i = 0; i < width * height; i++) {
        if (board[i] != nullptr) {
            updateDisplayMatrix(i);
            auto* individual = dynamic_cast<Individual*>(board[i]);
            if (individual != nullptr) {
                int coords = findFoodInRange(individual, individual->getVision());
                if (coords != -1 && dynamic_cast<Individual*>(futureBoard[coords]) == nullptr) {
                    futureBoard[coords] = individual;
                    individual->setCoords(coords / height, coords % height);
                    individual->eat();
                } else {
                    individual->move();
                    int newPosition = individual->getPosition();
                    if (futureBoard[newPosition] == nullptr) {
                        futureBoard[newPosition] = individual;
                    } else if (dynamic_cast<Individual*>(futureBoard[newPosition])){
                        int freePosition = findFreeSpot(individual, 5);
                        if (freePosition != -1) {
                            futureBoard[freePosition] = individual;
                        }
                    } else {
                        futureBoard[coords] = individual;
                    }
                }
            } else {
                auto* individualEaten = dynamic_cast<Individual*>(futureBoard[i]);
                if (!individualEaten) {
                    futureBoard[i] = board[i];
                }
            }
        }
    }
    window.draw(&displayMatrix[0], displayMatrix.size(), sf::Points);
    board = futureBoard;
    futureBoard.clear();
    futureBoard.resize(width * height);
}

Game::Game() : width(MAX_X),
               height(MAX_Y),
               numberOfIndividuals(promptUser("Specify the desired number of individuals", 10, 1000)),
               quantityOfFood(promptUser("Specify the desired quantity of food", 0,1500)) {
    window.create(sf::VideoMode(width * Cell::CELL_SIZE, height * Cell::CELL_SIZE + BOTTOM_BAR_HEIGHT), "Game of Life");
    initializeFont(font);
    board.resize(width * height);
    futureBoard.resize(width * height);
    epochCounter = 0;
    initialTime = getCurrentTime();
    generateCreatures();
    initializeDisplay();
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(15);
}

void Game::generateCreatures() {
    auto randomPositions = generateRandomArray(numberOfIndividuals + quantityOfFood, 0, width * height);
    for (int i = 0; i < numberOfIndividuals; i++) {
        Cell *individual = new Clairvoyant(randomPositions[i] / height, randomPositions[i] % height);
        board[randomPositions[i]] = individual;
    }
    for (int i = numberOfIndividuals; i < numberOfIndividuals + quantityOfFood; i++) {
        Cell *food = new Food(randomPositions[i] / height, randomPositions[i] % height);
        board[randomPositions[i]] = food;
    }

}

Game::~Game() {
    for (auto &cell : board) {
        delete cell;
    }
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
    if (board[i] == nullptr) {
        updateDisplayMatrix(i, sf::Color::Black);
    } else {
        updateDisplayMatrix(i, board[i]->getColor());
    }
}

int Game::findFreeSpot(Individual *individual, int radius) {
    int position = individual->getPosition();
    int x = position / height;
    int y = position % height;
    // check in the circle centered at (x, y) with radius i
    for (int j = x - radius; j <= x + radius; ++j) {
        for (int k = y - radius; k <= y + radius; ++k) {
            int newPos = j * height + k;
            if (newPos >= 0 && newPos < width * height && futureBoard[newPos] == nullptr) {
                return newPos;
            }
        }
    }
    return -1;
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
                if (food != nullptr && dynamic_cast<Individual*>(futureBoard[newPos]) == nullptr) {
                    return newPos;
                }
            }
        }
    }
    return -1;
}

void Game::showStatistics() {
    for (auto &i : raceDict) {
        std::cout << i.second << " - " << getPercentage(fitnessCache[i.first].second, fitnessCache[i.first].first) << std::endl;
    }
}
