//
// Created by anna on 3/25/23.
//

#include "Individual.h"
#include "Utils.h"
#include "Game.h"

Individual::Individual(int x, int y, int size, int direction, int speed) {
    this->x = x;
    this->y = y;
    this->size = size;
    this->direction = direction;
    this->speed = speed;
    this->health = LIFE_TIME;
}

Individual::Individual() {
    std :: cout << "Individual created" << std :: endl;
    this->x = randomIntegerFromInterval(0, MAX_X);
    this->y = randomIntegerFromInterval(0, MAX_Y);
    this->size = DEFAULT_SIZE;
    this->direction = randomIntegerFromInterval(0, NUMBERS_OF_DIRECTIONS);
    this->speed = DEFAULT_SPEED;
    this->health = LIFE_TIME;
}

Individual::Individual (const Individual &other) {
    this->x = other.x;
    this->y = other.y;
    this->size = other.size;
    this->direction = other.direction;
    this->speed = other.speed;
    this->health = other.health;
}

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

