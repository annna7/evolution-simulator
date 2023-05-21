#ifndef OOP_REDBULL_H
#define OOP_REDBULL_H

#include "Individual.h"

class RedBull : public Individual {
public:
    RedBull(int x, int y);
    [[nodiscard]] sf::Color getColor() override;
    [[nodiscard]] int getHunger() const override;
    [[nodiscard]] int getSpeed() const override;
};


#endif //OOP_REDBULL_H
