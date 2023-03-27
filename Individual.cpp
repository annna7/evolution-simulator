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

int Individual::getX() const {
    return x;
}

int Individual::getY() const {
    return y;
}

Individual::Individual() {
    std :: cout << "Individual created" << std :: endl;
    this->x = randomIntegerFromInterval(0, 500);
    this->y = randomIntegerFromInterval(0, 500);
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
    sf::CircleShape shape(size);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(x, y);
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
    if (x < MIN_X) {
        x = MAX_X;
    }
    if (x > MAX_X) {
        x = MIN_X;
    }
    if (y < MIN_Y) {
        y = MAX_Y;
    }
    if (y > MAX_Y) {
        y = MIN_Y;
    }
}

//void Individual::kill() {
//    Game::getInstance().removeIndividual(std::make_pair(x, y));
//    Individual::~Individual();
//}

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

