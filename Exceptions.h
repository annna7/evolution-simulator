#ifndef OOP_EXCEPTIONS_H
#define OOP_EXCEPTIONS_H

#include <stdexcept>
#include "IndividualType.h"


class InvalidIndividualException : public std::runtime_error {
public:
    explicit InvalidIndividualException();
    explicit InvalidIndividualException(const std::string &message);
};

class InvalidIndividualTypeException : public InvalidIndividualException {
public:
    explicit InvalidIndividualTypeException();
    explicit InvalidIndividualTypeException(const IndividualType &type);
};

class InvalidIndividualPositionException : public InvalidIndividualException {
public:
    explicit InvalidIndividualPositionException(int x, int y);
};

class InvalidFightingOutcomeException : public std::runtime_error {
public:
    explicit InvalidFightingOutcomeException();
};

class InvalidFightingStrategyType : public std::runtime_error {
public:
    explicit InvalidFightingStrategyType();
};

class RanOutOfEmptyPositionsException : public std::runtime_error {
public:
    explicit RanOutOfEmptyPositionsException(int x, int y, int radius);
};

class NoFoodException : public std::runtime_error {
public:
    explicit NoFoodException(int x, int y);
};

class NoSurvivorsException : public std::runtime_error {
public:
    explicit NoSurvivorsException(int epochNumber);
};

class ResourceLoadException : public std::runtime_error {
public:
    explicit ResourceLoadException(const std::string& file);
};

class FontLoadingException : public ResourceLoadException {
public:
    explicit FontLoadingException(const std::string& file, const std::string &fontName);
};

#endif //OOP_EXCEPTIONS_H
