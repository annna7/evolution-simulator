#pragma once

#include <ostream>

class Individual {
public:
    Individual(int x, int y, int size, int direction, int speed);
    Individual();
    Individual(const Individual &other);
    Individual& operator=(const Individual &other);
    ~Individual();
    friend std::ostream &operator<<(std::ostream &os, const Individual &individual);
    bool operator==(const Individual &rhs) const;
    void move();
    void update_life_time(int modifier);
    void draw() const;

private:
    int x, y, size, speed, direction, health;

    const static int DEFAULT_SPEED = 1;
    const static int DEFAULT_SIZE = 2;
    const static int RESET_DIRECTION_SEED = 15;
    const static int LIFE_TIME = 100;
    const static int NUMBERS_OF_DIRECTIONS = 8;
};