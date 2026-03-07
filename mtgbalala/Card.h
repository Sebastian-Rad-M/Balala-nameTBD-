#pragma once
#include <memory>
#include <string>
#include <vector>   
#include <iostream> 
#include "Effect.h"

struct modifier; 
class RoundTracker; 

class Card {
private:
    std::string name;
    int genericCost, redCost, blueCost, greenCost;
    std::vector<std::unique_ptr<IEffect>> effects;
    char rarity; // C, U, R, L
    std::shared_ptr<modifier> mod = nullptr;

public:
    Card() : name(""), genericCost(0), redCost(0), blueCost(0), greenCost(0),
             rarity('C'), mod(nullptr) {}

    Card(const std::string &name, int genericCost = 0, int redCost = 0,
         int blueCost = 0, int greenCost = 0, char rarity = 'C', 
         std::shared_ptr<modifier> mod = nullptr) 
         : name(name), genericCost(genericCost), redCost(redCost),
           blueCost(blueCost), greenCost(greenCost), rarity(rarity), mod(mod) {}

    Card(const Card& other) 
        : name(other.name), genericCost(other.genericCost), redCost(other.redCost),
          blueCost(other.blueCost), greenCost(other.greenCost), rarity(other.rarity), 
          mod(other.mod) 
    { //deep copy
        for (const auto& effect : other.effects) {
            effects.push_back(effect->clone());
        }
    }
    Card& operator=(const Card& other) {
        if (this != &other) {
            name = other.name;
            genericCost = other.genericCost;
            redCost = other.redCost;
            blueCost = other.blueCost;
            greenCost = other.greenCost;
            rarity = other.rarity;
            mod = other.mod;
            effects.clear();
            for (const auto& effect : other.effects) {
                effects.push_back(effect->clone());
            }
        }
        return *this;
    }

    ~Card() = default; //we love smart pointers
    
    friend std::ostream& operator<<(std::ostream& os, const Card& c) {
        os << "[" << c.rarity << "] " << c.name 
           << " (Cost: " << c.genericCost << "G, " << c.redCost << "R, " 
           << c.blueCost << "B, " << c.greenCost << "G)";
        return os;
    }
    void play(RoundTracker& state) {
        for (const auto& effect : effects) {
            effect->resolve(state);
        }
    }
    //random bs go go go
    const std::string &getName() const { return name; }
    int getGenericCost() const { return genericCost; }
    int getRedCost() const { return redCost; }
    int getBlueCost() const { return blueCost; }
    int getGreenCost() const { return greenCost; }
    char getRarity() const { return rarity; }
    int totalCost() const {
        return genericCost + redCost + blueCost + greenCost;
    }
    
   
};