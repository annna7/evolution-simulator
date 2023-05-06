//
// Created by anna on 5/6/23.
//

#ifndef OOP_CELL_H
#define OOP_CELL_H


#include <SFML/Graphics/Shape.hpp>

class Cell {
public:
    const static int CELL_SIZE = 3;
    virtual sf::Color getColor() = 0;
    virtual const sf::Shape *getShape() = 0;
};


#endif //OOP_CELL_H
