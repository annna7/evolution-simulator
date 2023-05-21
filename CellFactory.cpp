#include "Utils.h"
#include "Individual.h"
#include "Ascendant.h"
#include "Suitor.h"
#include "RedBull.h"
#include "Keystone.h"
#include "Clairvoyant.h"
#include "CellFactory.h"
#include "Exceptions.h"


std::shared_ptr<Ascendant> CellFactory::createAscendant(int x, int y) {
    return std::make_shared<Ascendant>(x, y);
}

std::shared_ptr<RedBull> CellFactory::createRedBull(int x, int y) {
    return std::make_shared<RedBull>(x, y);
}

std::shared_ptr<Keystone> CellFactory::createKeystone(int x, int y) {
    return std::make_shared<Keystone>(x, y);
}

std::shared_ptr<Clairvoyant> CellFactory::createClairvoyant(int x, int y) {
    return std::make_shared<Clairvoyant>(x, y);
}

std::shared_ptr<Food> CellFactory::createFood(int x, int y) {
    return std::make_shared<Food>(x, y);
}

std::shared_ptr<Individual> CellFactory::createSuitor(int x, int y) {
    switch (randomIntegerFromInterval(0, 3)) {
        case 0:
            return std::make_shared<Suitor<Ascendant>>(x, y);
        case 1:
            return std::make_shared<Suitor<RedBull>>(x, y);
        case 2:
            return std::make_shared<Suitor<Keystone>>(x, y);
        case 3:
            return std::make_shared<Suitor<Clairvoyant>>(x, y);
        default:
            return nullptr;
    }
}

std::shared_ptr<Individual> CellFactory::createIndividual(int x, int y, IndividualType type) {
    switch (type) {
        case ASCENDANT_TYPE:
            return createAscendant(x, y);
        case KEYSTONE_TYPE:
            return createKeystone(x, y);
        case REDBULL_TYPE:
            return createRedBull(x, y);
        case CLAIRVOYANT_TYPE:
            return createClairvoyant(x, y);
        case SUITOR_TYPE:
            return createSuitor(x, y);
        case INDIVIDUAL_TYPE_BEGIN:
            throw InvalidIndividualTypeException(INDIVIDUAL_TYPE_BEGIN);
        case INDIVIDUAL_TYPE_END:
            throw InvalidIndividualTypeException(INDIVIDUAL_TYPE_END);
        default:
            throw InvalidIndividualTypeException(type);
    }
}
