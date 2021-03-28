#include "../headers/fightclub.h"

Ability::Ability(std::string name, float power, float defense, float random) {
    this->power = power;
    this->defense = defense;
    this->random = random;
    this->name = name;
}

float Ability::getPower() {
    return this->power;
}

float Ability::getDefense() {
    return this->defense;
}

float Ability::getRandom() {
    return this->random;
}

std::string Ability::getName() {
    return this->name;
}
