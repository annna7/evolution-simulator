
#include "Individual.h"
#include <memory>
#include <utility>
#include "Utils.h"
#include "Exceptions.h"
#include "DefensiveFightingStrategy.h"
#include "OffensiveFightingStrategy.h"

Individual::Individual(int x, int y) : x(x), y(y), health(0), direction(randomIntegerFromInterval(0, NUMBERS_OF_DIRECTIONS - 1)), speed(DEFAULT_SPEED) {
    if (randomIntegerFromInterval(0, 1) == 0) {
        fightingStrategy = std::make_shared<OffensiveFightingStrategy>();
    } else {
        fightingStrategy = std::make_shared<DefensiveFightingStrategy>();
    }
}

std::ostream &operator<<(std::ostream &os, const Individual &individual) {
    os << "INDIVIDUAL - x: " << individual.x << " " << "y: " << individual.y << "\n";
    return os;
}

void Individual::eat() {
    health += 1;
}

void Individual::move() {
    x += getSpeed() * dirX[direction];
    y += getSpeed() * dirY[direction];
    if (randomIntegerFromInterval(0, RESET_DIRECTION_SEED) == 0) {
        direction = randomIntegerFromInterval(0, NUMBERS_OF_DIRECTIONS - 1);
    }
    try {
        checkCoordinates(x, y);
    } catch (const InvalidIndividualPositionException&) {
        if (x < 0) {
            x = OFFSET;
        } else if (x > MAX_X) {
            x = MAX_X - OFFSET;
        }

        if (y < 0) {
            y = OFFSET;
        } else if (y > MAX_Y) {
            y = MAX_Y - OFFSET;
        }
    }
}



bool Individual::operator==(const Individual &rhs) const {
    return x == rhs.x &&
           y == rhs.y &&
           speed == rhs.speed &&
           direction == rhs.direction &&
           health == rhs.health &&
           fightingStrategy == rhs.fightingStrategy;
}

Individual &Individual::operator=(const Individual &other) {
    if (this == &other) {
        return *this;
    }
    x = other.x;
    y = other.y;
    speed = other.speed;
    direction = other.direction;
    health = other.health;
    fightingStrategy = other.fightingStrategy;
    return *this;
}

Individual::~Individual() = default;

int Individual::getPosition() const {
    return y * MAX_Y + x;
}

int Individual::getVision() const {
    return Individual::DEFAULT_VISION;
}

int Individual::getHunger() const {
    return Individual::DEFAULT_HUNGER;
}

int Individual::getSpeed() const {
    return Individual::DEFAULT_SPEED;
}

bool Individual::checkIfAlive() const {
    return health >= getHunger();
}

void Individual::setCoords(int xx, int yy) {
    x = xx;
    y = yy;
}

std::shared_ptr<FightingStrategy> Individual::getFightingStrategy() {
    return fightingStrategy;
}

FightingOutcome Individual::fight(const std::shared_ptr<Individual>& individual) {
    return fightingStrategy->fight(individual->getFightingStrategy());
}

Individual::Individual(int x, int y, std::shared_ptr<FightingStrategy> fightingStrategy) : Individual(x, y) {
    this->fightingStrategy = std::move(fightingStrategy);
}

sf::Color Individual::getColor() const {
    return fightingStrategy ? colorMixer(getOwnColor(), fightingStrategy->getColor()) : getOwnColor();
}

