#include "Exceptions.h"
#include "Utils.h"
#include "IndividualType.h"

InvalidIndividualException::InvalidIndividualException() : runtime_error("Bad Individual.") {}

InvalidIndividualException::InvalidIndividualException(const std::string &message) : runtime_error(message) {}

InvalidIndividualTypeException::InvalidIndividualTypeException(const IndividualType &type) : InvalidIndividualException("Invalid individual type: " +
                                                                                                                                individualTypeToString(type)) {}

InvalidIndividualTypeException::InvalidIndividualTypeException() : InvalidIndividualException() {}

InvalidIndividualPositionException::InvalidIndividualPositionException(int x, int y) : InvalidIndividualException("Invalid individual position: (" +
                                                                                                                        std::to_string(x) + ", " +
                                                                                                                        std::to_string(y) + ")") {}

RanOutOfEmptyPositionsException::RanOutOfEmptyPositionsException(int x, int y, int radius) : runtime_error("Ran out of empty positions in radius " + std::to_string(radius) + " around (" +
                                                                                                                        std::to_string(x) + ", " +
                                                                                                                        std::to_string(y) + ")") {}

NoSurvivorsException::NoSurvivorsException(int epochNumber) : runtime_error("No survivors in epoch " + std::to_string(epochNumber) + ".") {}

ResourceLoadException::ResourceLoadException(const std::string &file) : runtime_error("Failed to load resource: " + file) {}

FontLoadingException::FontLoadingException(const std::string &file, const std::string &fontName) : ResourceLoadException("Failed to load font " + fontName + " from file " + file) {}


NoFoodException::NoFoodException(int x, int y) : runtime_error("No food at position (" + std::to_string(x) + ", " + std::to_string(y) + ") for our creature.") {}

InvalidFightingOutcomeException::InvalidFightingOutcomeException() : std::runtime_error("Invalid fighting outcome!") {}
