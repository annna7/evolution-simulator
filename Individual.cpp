//
// Created by anna on 3/25/23.
//

#include "Individual.h"
#include "Utils.h"
#include "Game.h"

Individual::Individual(int x, int y, int size, int direction, int speed) : x(x), y(y), size(size), speed(speed), direction(direction), health(LIFE_TIME) {}

Individual::Individual() : x(randomIntegerFromInterval(0, MAX_X)), y(randomIntegerFromInterval(0, MAX_Y)), size(DEFAULT_SIZE), speed(DEFAULT_SPEED), direction(randomIntegerFromInterval(0, NUMBERS_OF_DIRECTIONS)), health(LIFE_TIME) {}

Individual::Individual(const Individual &other) : x(other.x), y(other.y), size(other.size), speed(other.speed), direction(other.direction), health(other.health) {}

void Individual::draw() const {
    sf::CircleShape shape((float)size);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition((float)x, (float)y);
    Game::getInstance().draw(shape);
}

std::ostream &operator<<(std::ostream &os, const Individual &individual) {
    os << "INDIVIDUAL - x: " << individual.x << " " << "y: " << individual.y << "\n";
    return os;
}

void Individual::move() {
    x += speed * dirX[direction];
    y += speed * dirY[direction];
    if (randomIntegerFromInterval(0, RESET_DIRECTION_SEED) == 0) {
        direction = randomIntegerFromInterval(0, NUMBERS_OF_DIRECTIONS);
    }

    if (x < 0 || x > MAX_X) {
        y = 0;
        x = randomIntegerFromInterval(0, MAX_X);
    }
    if (y < 0 || y > MAX_Y) {
        y = 0;
        y = randomIntegerFromInterval(0, MAX_Y);
    }
}


void Individual::update_life_time(int modifier) {
    health += modifier;
}

bool Individual::operator==(const Individual &rhs) const {
    return x == rhs.x &&
           y == rhs.y &&
           size == rhs.size &&
           speed == rhs.speed &&
           direction == rhs.direction &&
           health == rhs.health;
}

Individual &Individual::operator=(const Individual &other) {
    x = other.x;
    y = other.y;
    size = other.size;
    speed = other.speed;
    direction = other.direction;
    health = other.health;
    return *this;
}

Individual::~Individual() {
    std::cout << "Individual destructor called\n";
}

