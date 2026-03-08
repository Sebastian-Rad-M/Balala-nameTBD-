#pragma once
#include <random>

class RNG {
private:
    // This private function holds the actual engine.
    // Because the variables are 'static', they are only created the VERY FIRST time 
    // this function is ever called, and then they stay alive forever.
    static std::mt19937& getEngine() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }

public:
    // A clean, global function to get a random number between min and max
    static int range(int min, int max) {
        std::uniform_int_distribution<> dist(min, max);
        return dist(getEngine());
    }

    // A clean way to expose the engine if you need it for std::shuffle!
    static std::mt19937& engine() {
        return getEngine();
    }
};