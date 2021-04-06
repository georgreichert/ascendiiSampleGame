#include "../headers/fightclub.h"

Team::Team(Fighter* fighter1, Fighter* fighter2, std::string name) {
    this->fighters[0] = fighter1;
    this->fighters[1] = fighter2;
    this->name = name;
}

Fighter* Team::getFighter(int index) {
    return this->fighters[index];
}

std::string Team::getName() {
    return this->name;
}

void Team::setPlayerType(bool type) {
    this->playerType = type;
}

bool Team::getPlayerType() {
    return this->playerType;
}

int Team::getVictories() {
    return this->victories;
}

int Team::getDefeats() {
    return this->defeats;
}

void Team::victory() {
    this->victories++;
}

void Team::defeat() {
    this->defeats++;
}
