#ifndef OOP_KEYSTONE_H
#define OOP_KEYSTONE_H

#include "Individual.h"
#include "Utils.h"


class Keystone : public Individual {
public:
    Keystone(int x, int y);
    [[nodiscard]] sf::Color getOwnColor() const override;
};


#endif //OOP_KEYSTONE_H
