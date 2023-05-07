#pragma once

#include <ostream>
#include "Cell.h"

// abstract class since it doesn't implement getColor()
class Individual : public Cell {
public:
    Individual(const Individual &other) = default;
    Individual(int x, int y);

    Individual& operator=(const Individual &other);
    ~Individual() override;
    friend std::ostream &operator<<(std::ostream &os, const Individual &individual);
    bool operator==(const Individual &rhs) const;
    [[nodiscard]] virtual int getSpeed() const;
    [[nodiscard]] virtual int getHunger() const;
    [[nodiscard]] virtual int getVision() const;
    [[nodiscard]] virtual int getType() const = 0;
    [[nodiscard]] int getPosition() const;
    void setCoords(int x, int y);
    void eat();
    void move();

    [[nodiscard]] bool checkIfAlive() const;

private:
    int x, y, health, direction, speed;
    const static int DEFAULT_HUNGER = 1;
    const static int DEFAULT_SPEED = 1;
    const static int DEFAULT_VISION = 2;
    const static int RESET_DIRECTION_SEED = 15;
    const static int NUMBERS_OF_DIRECTIONS = 8;
};