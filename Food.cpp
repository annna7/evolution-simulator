#include "Food.h"
#include "Utils.h"
#include <SFML/Graphics.hpp>

Food::Food(int x, int y) {
    this->x = x;
    this->y = y;
}

Food::Food() {
    this->x = randomIntegerFromInterval(MIN_X, MAX_X);
    this->y = randomIntegerFromInterval(MIN_Y, MAX_Y);
}

Food::Food(const Food &other) {
    this->x = other.x;
    this->y = other.y;
}

void Food::draw() const {
    sf::RectangleShape shape(sf::Vector2f(FOOD_SIZE, FOOD_SIZE));
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(x, y);
    Game::getInstance().draw(shape);
}

std::ostream &operator<<(std::ostream &os, const Food &food) {
    os << "FOOD - " << food.x << " " << food.y << "\n";
    return os;
}
