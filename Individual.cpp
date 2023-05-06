//
// Created by anna on 3/25/23.
//

#include "Individual.h"
#include "Utils.h"
#include "Game.h"

Individual::Individual(int x, int y, int direction, int speed) : x(x), y(y), speed(speed), direction(direction), health(LIFE_TIME) {}

Individual::Individual(int x, int y) : x(x), y(y), speed(DEFAULT_SPEED), direction(randomIntegerFromInterval(0, NUMBERS_OF_DIRECTIONS - 1)), health(LIFE_TIME) {}
Individual::Individual(const Individual &other) : x(other.x), y(other.y), speed(other.speed), direction(other.direction), health(other.health) {}


std::ostream &operator<<(std::ostream &os, const Individual &individual) {
    os << "INDIVIDUAL - x: " << individual.x << " " << "y: " << individual.y << "\n";
    return os;
}

void Individual::move() {
    x += speed * dirX[direction];
    y += speed * dirY[direction];
    if (randomIntegerFromInterval(0, RESET_DIRECTION_SEED) == 0) {
        direction = randomIntegerFromInterval(0, NUMBERS_OF_DIRECTIONS - 1);
    }

    const int OFFSET = 10;
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



bool Individual::operator==(const Individual &rhs) const {
    return x == rhs.x &&
           y == rhs.y &&
           speed == rhs.speed &&
           direction == rhs.direction &&
           health == rhs.health;
}

Individual &Individual::operator=(const Individual &other) {
    x = other.x;
    y = other.y;
    speed = other.speed;
    direction = other.direction;
    health = other.health;
    return *this;
}

Individual::~Individual() {
    std::cout << "Individual destructor called\n";
}

const sf::Shape *Individual::getShape() {
    auto *shape = new sf::RectangleShape(sf::Vector2f((float)CELL_SIZE, (float)CELL_SIZE));
    shape->setFillColor(sf::Color::Red);
    shape->setPosition((float)x, (float)y);
    return shape;
}

sf::Color Individual::getColor() {
    return sf::Color::Red;
}

int Individual::getPosition() const {
    return y * MAX_Y + x;
}

