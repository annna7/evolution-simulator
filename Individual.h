#pragma once

#include <ostream>
#include "Cell.h"

class Individual : public Cell {
public:
    const static int VISION = 2;

    Individual(const Individual &other) = default;
    Individual(int x, int y);

    Individual& operator=(const Individual &other);
    ~Individual() override;
    friend std::ostream &operator<<(std::ostream &os, const Individual &individual);
    bool operator==(const Individual &rhs) const;
    const sf::Shape *getShape() override;
    sf::Color getColor() override;
    void eat();
    void move();
    [[nodiscard]] int getPosition() const;

private:
    int x, y, health, direction, speed{};
    const static int HUNGER = 1;
    const static int SPEED = 1;
    const static int RESET_DIRECTION_SEED = 15;
    const static int NUMBERS_OF_DIRECTIONS = 8;
};