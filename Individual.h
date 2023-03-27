#pragma once

#include <ostream>

class Individual {
public:
    Individual(int x, int y, int size, int direction, int speed);
    Individual();
    Individual(const Individual &other);
    friend std::ostream &operator<<(std::ostream &os, const Individual &individual);
    void draw() const;
    void move();
    void update_life_time(int modifier);
    int getX() const;
    int getY() const;

    bool operator==(const Individual &rhs) const;

private:
    int x, y, size, speed, direction, health;
    const static int DEFAULT_SPEED = 1;
    const static int DEFAULT_SIZE = 2;
    const static int NUMBERS_OF_DIRECTIONS = 8;
    const static int RESET_DIRECTION_SEED = 15;
    const static int LIFE_TIME = 100;
};