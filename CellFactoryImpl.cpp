#include "CellFactory.cpp"

template<> std::shared_ptr<Suitor<Ascendant>> CellFactory::createSuitor<Ascendant>(int x, int y);
template<> std::shared_ptr<Suitor<RedBull>> CellFactory::createSuitor<RedBull>(int x, int y);
template<> std::shared_ptr<Suitor<Keystone>> CellFactory::createSuitor<Keystone>(int x, int y);
template<> std::shared_ptr<Suitor<Clairvoyant>> CellFactory::createSuitor<Clairvoyant>(int x, int y);