#ifndef OOP_CLAIRVOYANT_H
#define OOP_CLAIRVOYANT_H

#include "Individual.h"
#include "Utils.h"

class Clairvoyant : public Individual {
public:
    Clairvoyant(int x, int y);
    [[nodiscard]] int getHunger() const override;
    [[nodiscard]] int getVision() const override;
    [[nodiscard]] sf::Color getOwnColor() const override;
};

#endif //OOP_CLAIRVOYANT_H
