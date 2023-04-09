#include "Food.h"
#include "Utils.h"
#include "Game.h"
#include <SFML/Graphics.hpp>

Food::Food(int x, int y) : x(x), y(y) {}

Food::Food() : x(randomIntegerFromInterval(0, MAX_X)), y(randomIntegerFromInterval(0, MAX_Y)) {}

Food::Food(const Food &other) : x(other.x), y(other.y) {}

Food& Food::operator=(const Food &other) = default;

void Food::draw() const {
    sf::RectangleShape shape(sf::Vector2f((float)FOOD_SIZE, (float)FOOD_SIZE));
    shape.setFillColor(sf::Color::Green);
    shape.setPosition((float)x, (float)y);
    Game::getInstance().draw(shape);
}

std::ostream &operator<<(std::ostream &os, const Food &food) {
    os << "FOOD - " << food.x << " " << food.y << "\n";
    return os;
}

Food::~Food() {
    std::cout << "Food destructor called\n";
}