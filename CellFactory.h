//
// Created by anna on 5/14/23.
//

#ifndef OOP_CELLFACTORY_H
#define OOP_CELLFACTORY_H


#include "Individual.h"
#include "Utils.h"
#include "Ascendant.h"
#include "Suitor.h"
#include "RedBull.h"
#include "Keystone.h"
#include "Clairvoyant.h"

class CellFactory {
public:
    static std::shared_ptr<Ascendant> createAscendant(int x, int y);
    static std::shared_ptr<RedBull> createRedBull(int x, int y);
    static std::shared_ptr<Keystone> createKeystone(int x, int y);
    static std::shared_ptr<Clairvoyant> createClairvoyant(int x, int y);
    template <typename IndividualType>
    static std::shared_ptr<Suitor<IndividualType>> createSuitor(int x, int y);
    static std::shared_ptr<Individual> createSuitor(int x, int y);
    static std::shared_ptr<Food> createFood(int x, int y);
};


#endif //OOP_CELLFACTORY_H
