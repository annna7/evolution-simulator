#include "Food.h"
#include "Utils.h"
#include <SFML/Graphics.hpp>

Food::Food(int x, int y) : x(x), y(y) {}

Food::Food() : x(randomIntegerFromInterval(0, MAX_X)), y(randomIntegerFromInterval(0, MAX_Y)) {}

Food::Food(const Food &other) : x(other.x), y(other.y) {}

Food& Food::operator=(const Food &other) = default;

std::ostream &operator<<(std::ostream &os, const Food &food) {
    os << "FOOD - " << food.x << " " << food.y << "\n";
    return os;
}

Food::~Food() {
    std::cout << "Food destructor called\n";
}

sf::Color Food::getColor() {
    return {0, 100, 0};
}
