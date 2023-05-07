#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <SFML/Graphics/Font.hpp>

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
        std::cout << "Error loading font\n";
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

long long getCurrentTime() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
}

std::string getPercentage(int newStat, int oldStat) {
    return "Old: " + std::to_string(oldStat) + " New: " + std::to_string(newStat) + " " + std::to_string(newStat * 100.0 / oldStat) + "%";
}