#include <iostream>
#include <string>
#include <random>
#include <SFML/Graphics/Font.hpp>
#include "Exceptions.h"
#include "Utils.h"

int promptUser(const std::string& message, int mn, int mx) {
    int input;
    do {
        std::cout << message << " (" << mn << "-" << mx << "): ";
        std::cin >> input;
    } while (input < mn || input > mx);
    return input;
}

int randomIntegerFromInterval(int mn, int mx) {
    // generate random integer in interval mn, max using <random>
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(mn, mx);
    return dis(gen);
}

void initializeFont(sf::Font& font) {
    if (!font.loadFromFile("assets/RobotoMono-Regular.ttf")) {
        throw FontLoadingException("assets/RobotoMono-Regular.ttf", "Roboto Mono");
    }
}

// generate size distinct random numbers in interval [mn, mx)
// using the Fisher Yates shuffle algorithm
std::vector<int> generateRandomArray(int size, int mn, int mx) {
    std::vector<int> v;
    for (int i = mn; i < mx; i++) {
        v.push_back(i);
    }
    for (int i = 0; i < size; i++) {
        int j = randomIntegerFromInterval(i, mx - 1);
        std::swap(v[i], v[j]);
    }
    v.resize(size);
    return v;
}


std::string getPercentage(int newStat, int oldStat) {
    if (oldStat == 0) {
        return "N/A";
    } else {
        return std::to_string((newStat * 100) / oldStat) + "%";
    }
}

void checkCoordinates(int x, int y) {
    if (x < 0 || x >= MAX_X || y < 0 || y >= MAX_Y) {
        throw InvalidIndividualPositionException(x, y);
    }
}

void checkCoordinates(int pos) {
    return checkCoordinates(pos / MAX_X, pos % MAX_X);
}

sf::Color colorMixer(const sf::Color& color1, const sf::Color& color2) {
    sf::Uint8 red = (color1.r + color2.r) / 2;
    sf::Uint8 green = (color1.g + color2.g) / 2;
    sf::Uint8 blue = (color1.b + color2.b) / 2;

    return {red, green, blue};
}