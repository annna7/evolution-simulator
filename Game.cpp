#include <iostream>
#include "Game.h"
#include "Food.h"
#include "Individual.h"
#include "Cell.h"
#include "RedBull.h"
#include "Keystone.h"
#include "CellFactory.h"
#include "Clairvoyant.h"
#include "Ascendant.h"
#include <SFML/Graphics.hpp>

const std::unordered_map<int, std::string> Game::raceDict = {
        {RED_BULL, "RedBull"},
        {KEY_STONE, "Keystone"},
        {CLAIRVOYANT, "Clairvoyant"},
        {ASCENDANT, "Ascendant"},
        {SUITOR, "Suitor"}
};

Game &Game::getInstance() {
    static Game instance;
    return instance;
}

// Total number of survivors: p1 * x1 + p2 * x2 + ...
// Total number of individuals: x1 + x2 + ...
// Number of individuals of given species, proportional to their fitness: (p1 * x1 / (total number of survivors)) * (total number of individuals)
std::unordered_map<int, int> Game::computeNewGeneration() {
    std::unordered_map<int, int> newGeneration;
    int totalIndividuals = 0;
    int totalSurvivors = 0;
    for (auto &it : fitnessMap) {
        totalSurvivors += it.second.second;
        totalIndividuals += it.second.first;
    }
    try {
        for (auto &it : fitnessMap) {
            newGeneration[it.first] = it.second.first == 0 ? 0 : (int) ((1.0 * it.second.second / it.second.first) * it.second.first * totalIndividuals) / totalSurvivors;
        }
    } catch (std::exception &e) {
        std::cout << e.what() << "\n";
    }

    return newGeneration;
}

void Game::computeFitness() {
    for (auto &cell : board) {
        if (cell != nullptr) {
            // check if the cell has the same type as individual
            // for instance, if I pass a Redbull, check if the cell is a Redbull
            auto individualCell = dynamic_pointer_cast<Individual>(cell);
            if (individualCell != nullptr) {
                fitnessMap[individualCell->getType()].first += 1;
                if (!individualCell->checkIfAlive()) {
                    board[individualCell->getPosition()] = nullptr;
                } else {
                    fitnessMap[individualCell->getType()].second += 1;
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
    computeFitness();
    showStatistics();
    resetGeneration(computeNewGeneration());
    isPaused = true;
}

void Game::menuDisplay() {
    sf::Text message = sf::Text("Epoch: " + std::to_string(epochCounter) + " has ended! Press SPACE to spawn an evolved generation!", font);
    message.setPosition(20, (float) height * Cell::CELL_SIZE);
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
            sf::Time elapsed = clock.getElapsedTime(); // get the elapsed time since the last call to getElapsedTime()
            if (elapsed.asMilliseconds() >= EPOCH_DURATION) {
                endEpoch();
            } else {
                display();
            }
        } else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                isPaused = false;
                clock.restart();
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
            auto individual = dynamic_pointer_cast<Individual>(board[i]);
            if (individual != nullptr) {
                int coords = findFoodInRange(individual, individual->getVision());
                if (coords != -1 && dynamic_pointer_cast<Individual>(futureBoard[coords]) == nullptr) {
                    futureBoard[coords] = individual;
                    individual->setCoords(coords / height, coords % height);
                    individual->eat();
                } else {
                    individual->move();
                    int newPosition = individual->getPosition();
                    if (newPosition > width * height - 1) {
                        newPosition = newPosition % (width * height);
                    }
                    if (futureBoard[newPosition] == nullptr) {
                        futureBoard[newPosition] = individual;
                    } else if (dynamic_pointer_cast<Individual>(futureBoard[newPosition])){
                        // IMPLEMENT SUITOR HERE
                        int freePosition = findFreeSpot(individual, 5);
                        if (freePosition != -1) {
                            futureBoard[freePosition] = individual;
                        }
                    } else if (coords != -1) {
                        futureBoard[coords] = individual;
                    }
                }
            } else {
                auto individualEaten = dynamic_pointer_cast<Individual>(futureBoard[i]);
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
               keystoneNumber(promptUser("[YELLOW] Specify the desired number of Keystone's (no special abilities, but can sustain on a small quantity of food):", 0, 600)),
               clairvoyantNumber(promptUser("[BLUE] Specify the desired number of Clairvoyant's (can spot food from afar):", 0, 600)),
               redBullNumber(promptUser("[RED] Specify the desired number of RedBull's (fast on their feet, but high hunger):", 0, 600)),
               ascendantNumber(promptUser("[PINK] Specify the desired number of Ascendant's (become overpowered once they eat the first time):", 0, 600)),
               suitorNumber(promptUser("[GREEN] Specify the desired number of Suitor's (each Suitor wants to mate with a specific breed of individuals described above.):", 0, 600)),
               quantityOfFood(promptUser("[DARK GREEN] Specify the desired quantity of food", 0,2000)) {
    window.create(sf::VideoMode(width * Cell::CELL_SIZE, height * Cell::CELL_SIZE + BOTTOM_BAR_HEIGHT), "Game of Life");
    initializeFont(font);
    epochCounter = 0;
    resetBoard();
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(15);
}

void Game::generateCells() {
    board.clear();
    futureBoard.clear();
    board.resize(width * height);
    futureBoard.resize(width * height);
    int totalIndividuals = keystoneNumber + clairvoyantNumber + redBullNumber + ascendantNumber;
    auto randomPositions = generateRandomArray(totalIndividuals + quantityOfFood, 0, width * height);
    for (int i = 0; i < keystoneNumber; i++) {
        board[randomPositions[i]] = CellFactory::createKeystone(randomPositions[i] / height, randomPositions[i] % height);
    }
    for (int i = keystoneNumber; i < keystoneNumber + clairvoyantNumber; i++) {
        board[randomPositions[i]] = CellFactory::createClairvoyant(randomPositions[i] / height, randomPositions[i] % height);
    }
    for (int i = keystoneNumber + clairvoyantNumber; i < keystoneNumber + clairvoyantNumber + redBullNumber; i++) {
        board[randomPositions[i]] = CellFactory::createRedBull(randomPositions[i] / height, randomPositions[i] % height);
    }
    for (int i = keystoneNumber + clairvoyantNumber + redBullNumber; i < totalIndividuals; i++) {
        board[randomPositions[i]] = CellFactory::createAscendant(randomPositions[i] / height, randomPositions[i] % height);
    }
    for (int i = totalIndividuals; i < totalIndividuals + quantityOfFood; i++) {
        board[randomPositions[i]] = CellFactory::createFood(randomPositions[i] / height, randomPositions[i] % height);
    }
}

Game::~Game() {
    std::cout << "Destructor called\n";
}

std::ostream &operator<<(std::ostream &os, const Game &game) {
    os << " width: " << game.width << " height: " << game.height << " numberOfIndividuals: " << game.keystoneNumber + game.clairvoyantNumber + game.redBullNumber
       << " numberOfFood: " << game.quantityOfFood;
    return os;
}

void Game::initializeDisplay() {
    displayMatrix.resize(width * height * Cell::CELL_SIZE * Cell::CELL_SIZE);
    for (int i = 0; i < height * Cell::CELL_SIZE; ++i) {
        for (int j = 0; j < width * Cell::CELL_SIZE; ++j) {
            displayMatrix[i * width * Cell::CELL_SIZE + j] = sf::Vertex(sf::Vector2f((float)j, (float)i), sf::Color::Black);
        }
    }
}

void Game::updateDisplayMatrix(int i, sf::Color color) {
    int x = i / height;
    int y = i % height;
    for (int j = 0; j < Cell::CELL_SIZE; ++j) {
        for (int k = 0; k < Cell::CELL_SIZE; ++k) {
            displayMatrix[(x * Cell::CELL_SIZE + j) * width * Cell::CELL_SIZE + y * Cell::CELL_SIZE + k] =
                    sf::Vertex(sf::Vector2f((float)(y * Cell::CELL_SIZE + k), (float)(x * Cell::CELL_SIZE + j)), color);
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

int Game::findFreeSpot(const std::shared_ptr<Individual>& individual, int radius) {
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

int Game::findFoodInRange(const std::shared_ptr<Individual>& individual, int radius) {
    int position = individual->getPosition();
    int x = position / height;
    int y = position % height;
    // check in the circle centered at (x, y) with radius i
    for (int j = x - radius; j <= x + radius; ++j) {
        for (int k = y - radius; k <= y + radius; ++k) {
            int newPos = j * height + k;
            if (newPos >= 0 && newPos < width * height && board[newPos] != nullptr) {
                auto food = std::dynamic_pointer_cast<Food>(board[newPos]);
                if (food && !std::dynamic_pointer_cast<Individual>(futureBoard[newPos])) {
                    return newPos;
                }
            }
        }
    }
    return -1;
}

int Game::getTotalSurvivalRate() {
    int totalSurvivalRate = 0;
    int totalIndividuals = 0;
    for (auto &i : raceDict) {
        totalSurvivalRate += fitnessMap[i.first].second;
        totalIndividuals += fitnessMap[i.first].first;
    }
    return (int) (100.0 * totalSurvivalRate / totalIndividuals);
}

void Game::showStatistics() {
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::White);
    text.setPosition(20, (float)height * Cell::CELL_SIZE + 20);
    std::string output;
    for (auto &i : raceDict) {
        // append to text
        output += i.second + " - " + getPercentage(fitnessMap[i.first].second, fitnessMap[i.first].first) + "( " + std::to_string(fitnessMap[i.first].second) + " / " + std::to_string(fitnessMap[i.first].first) + " )\n";
    }
    output += "Total survival rate: " + std::to_string(getTotalSurvivalRate()) + "%\n";
    text.setString(output);
    window.draw(text);
}

void Game::resetGeneration(std::unordered_map<int, int> generation) {
    keystoneNumber = generation[KEY_STONE];
    clairvoyantNumber = generation[CLAIRVOYANT];
    redBullNumber = generation[RED_BULL];
    ascendantNumber = generation[ASCENDANT];
    resetBoard();
}

void Game::resetBoard() {
    fitnessMap.clear();
    generateCells();
    initializeDisplay();
}
