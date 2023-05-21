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
#include "Suitor.h"
#include "IndividualType.h"
#include "FightingStrategyType.h"


// altfel crapa
template <typename T> class Suitor;

class Game {
public:
    static Game &getInstance();
    void run();
    Game(const Game &other) = delete;
    Game& operator=(const Game &other) = delete;
    ~Game();
    friend std::ostream &operator<<(std::ostream &os, const Game &game);
    template <typename T>
    bool checkSuitor(std::shared_ptr<Individual> a, std::shared_ptr<T> b);

private:
    int killedIndividuals;
    int matingsOccurred;
    std::unordered_map<IndividualType, int> survivorMap;
    std::vector<std::shared_ptr<Cell>> board;
    std::vector<std::shared_ptr<Cell>> futureBoard;
    std::vector<sf::Vertex> displayMatrix;
    std::unordered_map<IndividualType, int> currentGeneration;
    std::unordered_map<FightingStrategyType, int> fightingStrategyMap;
    int width, height;
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
    static const int BOTTOM_BAR_HEIGHT = 150;
    void endEpoch();
    void menuDisplay();
    void computeFitness();
    const static std::unordered_map<int, std::string> raceDict;
    void showStatistics();
    int findFoodInRange(const std::shared_ptr<Individual>&, int radius);
    std::unordered_map<IndividualType, int> computeNewGeneration();
    void resetBoard();
    int getTotalSurvivalRate() const;

    template <typename K>
    void mate(std::shared_ptr<K> indiv, std::shared_ptr<Suitor<K>> suitor);
    int findFreeSpot(int pos, int radius);

    template <typename T>
    void produceOffspring(int pos);
    void assertFitnessOfIndividual(const std::shared_ptr<Individual>& individual);
    void resetGeneration(std::unordered_map<IndividualType, int> generation);
    int getTotalIndividuals() const;
    bool performSuitorCheck(const std::shared_ptr<Individual>& individual, const std::shared_ptr<Individual>& suitorCandidate);
    void handleInteraction(const std::shared_ptr<Individual>& individual1, const std::shared_ptr<Individual>& individual2);
    void handleFightingOutcome(const std::shared_ptr<Individual> &individual1, const std::shared_ptr<Individual> &individual2, FightingOutcome fightingOutcome);

    int getTotalSurvivors();
};
