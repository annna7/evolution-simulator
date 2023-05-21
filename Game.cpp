#include <iostream>
#include "Game.h"
#include "Food.h"
#include "Individual.h"
#include "Cell.h"
#include "CellFactory.h"
#include "IndividualType.h"
#include "Exceptions.h"
#include "DefensiveFightingStrategy.h"
#include "OffensiveFightingStrategy.h"
#include <SFML/Graphics.hpp>


template<typename K>
void Game::produceOffspring(int pos) {
    auto freeSpot = findFreeSpot(pos, 15);
    auto offspring = CellFactory::createSuitor<K>(freeSpot / width, freeSpot % width);

    // Each baby starts off with 3 food points at birth.
    for (int i = 0; i < 3; ++i) {
        offspring->eat();
    }

    futureBoard[freeSpot] = offspring;
}

template<typename K>
void Game::mate(std::shared_ptr<K> indiv, std::shared_ptr<Suitor<K>> suitor) {
    if (indiv == nullptr || suitor == nullptr) {
        return;
    }

    // When a couple mates, they can either produce one, two or three babies - this number gets chosen randomly.
    int offspringQuantity = randomIntegerFromInterval(1, 3);
    for (int i = 0; i < offspringQuantity; ++i) {
        // If there are no more empty spots on the board, the mating process stops.
        try {
            produceOffspring<K>(indiv->getPosition());
        } catch (const RanOutOfEmptyPositionsException &e) {
            std::cout << e.what() << std::endl;
        }
    }
    std::cout << "Successful mating!" << std::endl;
}


Game &Game::getInstance() {
    static Game instance;
    return instance;
}

// Total number of survivors: p1 * x1 + p2 * x2 + ...
// Total number of individuals: x1 + x2 + ...
// Number of individuals of given species, proportional to their fitness: (p1 * x1 / (total number of survivors)) * (total number of individuals)
std::unordered_map<IndividualType, int> Game::computeNewGeneration() {
    std::unordered_map<IndividualType, int> newGeneration;
    int totalIndividuals = getTotalIndividuals();
    int totalSurvivors = getTotalSurvivors();
    if (totalSurvivors == 0) {
        throw NoSurvivorsException(epochCounter);
    }
    for (auto type = (IndividualType)(INDIVIDUAL_TYPE_BEGIN + 1); type != INDIVIDUAL_TYPE_END; type = (IndividualType) (type + 1)) {
        newGeneration[type] = currentGeneration[type] == 0 ? 0 : (int) ((1.0 * survivorMap[type] / currentGeneration[type]) * currentGeneration[type] * totalIndividuals) / totalSurvivors;
    }
    return newGeneration;
}

void Game::assertFitnessOfIndividual(const std::shared_ptr<Individual>& individual) {
    checkCoordinates(individual->getPosition());
    if (!individual->checkIfAlive()) {
        board[individual->getPosition()] = nullptr;
    } else {
        if (dynamic_pointer_cast<Keystone>(individual)) {
            survivorMap[KEYSTONE_TYPE] += 1;
        } else if (std::dynamic_pointer_cast<Clairvoyant>(individual)) {
            survivorMap[CLAIRVOYANT_TYPE] += 1;
        } else if (std::dynamic_pointer_cast<RedBull>(individual)) {
            survivorMap[REDBULL_TYPE] += 1;
        } else if (std::dynamic_pointer_cast<Ascendant>(individual)) {
            survivorMap[ASCENDANT_TYPE] += 1;
        } else {
            survivorMap[SUITOR_TYPE] += 1;
        }

        if (individual->getFightingStrategy() == nullptr) {
            fightingStrategyMap[LOVER_TYPE] += 1;
        } else if (std::dynamic_pointer_cast<DefensiveFightingStrategy>(individual->getFightingStrategy())) {
            fightingStrategyMap[DEFENSIVE_TYPE] += 1;
        } else if (std::dynamic_pointer_cast<OffensiveFightingStrategy>(individual->getFightingStrategy())) {
            fightingStrategyMap[OFFENSIVE_TYPE] += 1;
        }
    }
}

void Game::computeFitness() {
    for (auto &cell : board) {
        if (cell != nullptr) {
            // check if the cell has the same type as individual
            // for instance, if I pass a Redbull, check if the cell is a Redbull
            auto individualCell = dynamic_pointer_cast<Individual>(cell);
            if (individualCell != nullptr) {
                try {
                    assertFitnessOfIndividual(individualCell);
                } catch (const InvalidIndividualPositionException &e) {
                    std::cout << e.what() << std::endl;
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
    try {
        resetGeneration(computeNewGeneration());
    } catch (const NoSurvivorsException &e) {
        std::cout << e.what() << std::endl;
        std::cout << "Game over!" << std::endl;
        window.close();
    }
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
                try {
                    int coords = findFoodInRange(individual, individual->getVision());
                    if (!std::dynamic_pointer_cast<Individual>(futureBoard[coords])) {
                        futureBoard[coords] = individual;
                        individual->setCoords(coords / width, coords % width);
                        individual->eat();
                    }
                } catch (const NoFoodException&) {
                    individual->move();
                    int newPosition = individual->getPosition();
                    try {
                        checkCoordinates(newPosition);
                        if (auto individualFound = dynamic_pointer_cast<Individual>(futureBoard[newPosition])) {
                            try {
                                handleInteraction(individual, individualFound);
                            } catch (const InvalidFightingOutcomeException& e) {
                                std::cout << e.what() << std::endl;
                            }
                        } else {
                            futureBoard[newPosition] = individual;
                        }
                    } catch (const InvalidIndividualPositionException&) {}
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
               height(MAX_Y) {
    currentGeneration[KEYSTONE_TYPE] = promptUser("[YELLOW] Specify the desired number of Keystone's (no special abilities, but can sustain on a small quantity of food):", 0, 600);
    currentGeneration[CLAIRVOYANT_TYPE] = promptUser("[BLUE] Specify the desired number of Clairvoyant's (can spot food from afar):", 0, 600);
    currentGeneration[REDBULL_TYPE] = promptUser("[RED] Specify the desired number of RedBull's (fast on their feet, but very hungry!)", 0, 600);
    currentGeneration[ASCENDANT_TYPE] = promptUser("[PINK] Specify the desired number of Ascendant's (become much stronger once they encounter food for the first time", 0, 600);
    currentGeneration[SUITOR_TYPE] = promptUser("[SUITOR] Specify the desired number of Suitor's - each Suitor wants to mate with a specific breed of Individuals. The type of Suitor gets chosen randomly at spawn time.",
                                                0, 600);
    quantityOfFood = promptUser("[DARK GREEN] Specify the desired quantity of food", 0, 2500);
    clock.restart();
    window.create(sf::VideoMode(width * Cell::CELL_SIZE, height * Cell::CELL_SIZE + BOTTOM_BAR_HEIGHT), "Game of Life");

    // testing to see why cppcheck fails
    std::shared_ptr<Ascendant> ascendant = std::make_shared<Ascendant>(0, 0);
    std::cout << ascendant->getHunger() << std::endl;

    try {
        initializeFont(font);
    } catch (const FontLoadingException &e) {
        std::cout << e.what() << std::endl;
    }

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
    int lowerBound = 0;

    std::cout << getTotalIndividuals() << std::endl;

    auto randomPositions = generateRandomArray(getTotalIndividuals() + quantityOfFood, 0, width * height);

    for (auto type = (IndividualType)(INDIVIDUAL_TYPE_BEGIN + 1); type != INDIVIDUAL_TYPE_END; type = (IndividualType)(type + 1)) {
        for (int i = lowerBound; i < lowerBound + currentGeneration[type]; i++) {
            try {
                board[randomPositions[i]] = CellFactory::createIndividual(randomPositions[i] / height, randomPositions[i] % height, type);
            } catch (InvalidIndividualTypeException &e) {
                std::cout << e.what() << std::endl;
            }
        }
        lowerBound += currentGeneration[type];
    }

    for (int i = lowerBound; i < lowerBound + quantityOfFood; i++) {
        board[randomPositions[i]] = CellFactory::createFood(randomPositions[i] / height, randomPositions[i] % height);
    }

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

int Game::findFreeSpot(int pos, int radius) {
    int x = pos / height;
    int y = pos % height;
    // check in the circle centered at (x, y) with radius i
    for (int j = x - radius; j <= x + radius; ++j) {
        for (int k = y - radius; k <= y + radius; ++k) {
            int newPos = j * height + k;
            if (newPos >= 0 && newPos < width * height && futureBoard[newPos] == nullptr) {
                return newPos;
            }
        }
    }
    throw RanOutOfEmptyPositionsException(x, y, radius);
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
    throw NoFoodException(x, y);
}

int Game::getTotalIndividuals() const {
    int totalIndividuals = 0;
    for (auto individualType = (IndividualType)(INDIVIDUAL_TYPE_BEGIN + 1); individualType != INDIVIDUAL_TYPE_END; individualType = (IndividualType)(individualType + 1)) {
        totalIndividuals += currentGeneration.at(individualType);
    }
    return totalIndividuals;
}

int Game::getTotalSurvivalRate() const {
    int totalSurvivalRate = 0;
    for (auto individualType = (IndividualType)(INDIVIDUAL_TYPE_BEGIN + 1); individualType != INDIVIDUAL_TYPE_END; individualType = (IndividualType)(individualType + 1)) {
        totalSurvivalRate += survivorMap.at(individualType);
    }
    return (int) (100.0 * totalSurvivalRate / getTotalIndividuals());
}

void Game::showStatistics() {
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::White);
    text.setPosition(20, (float)height * Cell::CELL_SIZE + 20);
    std::string output;

    for (auto type = (IndividualType)(INDIVIDUAL_TYPE_BEGIN + 1); type != INDIVIDUAL_TYPE_END; type = IndividualType(type + 1)) {
        output += individualTypeToString(type) + ": " +
                  getPercentage(survivorMap[type], currentGeneration[type]) + " survived. "
                  "( " + std::to_string(survivorMap[type]) + " / " + std::to_string(currentGeneration[type]) + ")\n";
    }

    for (auto type = (FightingStrategyType)(FIGHTING_TYPE_BEGIN + 1); type != FIGHTING_TYPE_END; type = FightingStrategyType(type + 1)) {
        output += fightingStrategyTypeToString(type) + ": " + getPercentage(fightingStrategyMap[type], getTotalSurvivors()) + "   ";
    }

    output += "\nTotal survival rate: " + std::to_string(getTotalSurvivalRate()) + "%\n";
    text.setString(output);
    window.draw(text);
}

void Game::resetGeneration(std::unordered_map<IndividualType, int> generation) {
    for (auto individualType = (IndividualType)(INDIVIDUAL_TYPE_BEGIN + 1); individualType != INDIVIDUAL_TYPE_END; individualType = (IndividualType)(individualType + 1)) {
        currentGeneration[individualType] = generation[individualType];
        survivorMap[individualType] = 0;
    }
    for (auto fightingStrategyType = (FightingStrategyType)(FIGHTING_TYPE_BEGIN + 1); fightingStrategyType != FIGHTING_TYPE_END; fightingStrategyType = (FightingStrategyType)(fightingStrategyType + 1)) {
        fightingStrategyMap[fightingStrategyType] = 0;
    }
    resetBoard();
}

void Game::resetBoard() {
    survivorMap.clear();
    generateCells();
    initializeDisplay();
}


template <typename T>
bool Game::checkSuitor(std::shared_ptr<Individual> a, std::shared_ptr<T> b) {
    if (dynamic_pointer_cast<Suitor<T>>(a)) {
        mate<T>(b, dynamic_pointer_cast<Suitor<T>>(a));
        return true;
    }
    return false;
}

Game::~Game() {
    std::cout << "Destructor called\n";
}

std::ostream &operator<<(std::ostream &os, const Game &game) {
    os << " width: " << game.width << " height: " << game.height << " numberOfIndividuals: " << game.getTotalIndividuals()
       << " numberOfFood: " << game.quantityOfFood;
    return os;
}

bool Game::performSuitorCheck(const std::shared_ptr<Individual>& individual, const std::shared_ptr<Individual>& suitorCandidate) {
    // call check suitor for individual's type
    if (checkSuitor<Clairvoyant>(suitorCandidate, dynamic_pointer_cast<Clairvoyant>(individual))) {
        return true;
    }
    if (checkSuitor<RedBull>(suitorCandidate, dynamic_pointer_cast<RedBull>(individual))) {
        return true;
    }
    if (checkSuitor<Keystone>(suitorCandidate, dynamic_pointer_cast<Keystone>(individual))) {
        return true;
    }
    if (checkSuitor<Ascendant>(suitorCandidate, dynamic_pointer_cast<Ascendant>(individual))) {
        return true;
    }
    return false;
}

void Game::handleInteraction(const std::shared_ptr<Individual>& individual1, const std::shared_ptr<Individual>& individual2) {
    if (individual1->getFightingStrategy() == nullptr && individual2->getFightingStrategy() == nullptr) {
        handleFightingOutcome(individual1, individual2, LIVE_LIVE);
    } else if (individual1->getFightingStrategy() == nullptr) {
        performSuitorCheck(individual2, individual1);
    } else if (individual2->getFightingStrategy() == nullptr) {
        performSuitorCheck(individual1, individual2);
    } else {
        handleFightingOutcome(individual1, individual2, individual1->fight(individual2));
    }
}

void Game::handleFightingOutcome(const std::shared_ptr<Individual>& individual1, const std::shared_ptr<Individual>& individual2, FightingOutcome fightingOutcome) {
    switch (fightingOutcome) {
        case LIVE_LIVE: {
            try {
                int freePosition = findFreeSpot(individual1->getPosition(), 5);
                futureBoard[freePosition] = individual1;
            } catch (const RanOutOfEmptyPositionsException &e) {
                std::cout << e.what() << std::endl;
            }
            break;
        }
        case LIVE_DIE: {
            futureBoard[individual1->getPosition()] = individual1;
            break;
        }
        case DIE_LIVE: {
            futureBoard[individual2->getPosition()] = individual2;
            break;
        }
        default:
            throw InvalidFightingOutcomeException();
    }
}

int Game::getTotalSurvivors() {
    int totalSurvivors = 0;
    for (auto individualType = (IndividualType)(INDIVIDUAL_TYPE_BEGIN + 1); individualType != INDIVIDUAL_TYPE_END; individualType = (IndividualType)(individualType + 1)) {
        totalSurvivors += survivorMap[individualType];
    }
    return totalSurvivors;
}
