#include "../headers/fightclub.h"

Fighter::Fighter(std::string name, float maxHP, float baseDMG, float baseDEF, float blockBonus, Ability* ab1, Ability* ab2, Sprite* sprite) {
    this->name = name;
    this->maxHP = maxHP;
    this->currentHP = maxHP;
    this->baseDMG = baseDMG;
    this->baseDEF = baseDEF;
    this->blockBonus = blockBonus;
    this->abilities[0] = ab1;
    this->abilities[1] = ab2;
    this->sprite = sprite;
}

Fighter::~Fighter() {
    delete this->sprite;
}

std::string Fighter::getName() {
    return this->name;
}

float Fighter::getMaxHP() {
    return this->maxHP;
}

float Fighter::getCurrentHP() {
    return this->currentHP;
}

float Fighter::getBaseDMG() {
    return this->baseDMG;
}

float Fighter::getBaseDEF() {
    return this->baseDEF;
}

float Fighter::getBlockBonus() {
    return this->blockBonus;
}

bool Fighter::isBlocking() {
    return this->blocking;
}

float Fighter::takeHit(float DMG) {
    float debugCurrentHP = this->currentHP;
    this->currentHP -= DMG / this->baseDEF / (this->currentDEFfactor + (this->blocking ? this->blockBonus : 0.0f));
    if (this->currentHP < 0) {
        this->currentHP = 0;
    }
    this->blocking = false;
    this->sprite->setColor(COLOR_WHITE);
    DebugLog::log(this->name + " was hit for " + std::to_string(DMG) + "DMG and lost " + std::to_string(debugCurrentHP - this->currentHP) + "HP");
}

float Fighter::hit(int index) {
    this->currentDMGfactor = this->abilities[index]->getPower();
    this->currentDEFfactor = this->abilities[index]->getDefense();
    this->currentRandomModifier = this->abilities[index]->getRandom();
//    return this->baseDMG * (this->currentDMGfactor + (((float)(rand() % 11)) / 10) * this->currentRandomModifier * (rand() % 2 ? -1 : 1));
    float debugRand1 = ((float)(rand() % 11)) / 10;
    int debugRand2 = (rand() % 2 ? -1 : 1);
    float debugReturn = this->baseDMG * (this->currentDMGfactor + debugRand1 * this->currentRandomModifier * debugRand2);
    DebugLog::log(this->name + " uses " + this->abilities[index]->getName() + " to deal " + std::to_string(debugReturn) + "DMG\n" +
                  "Rand 1: " + std::to_string(debugRand1) + "\nRand 2: " + std::to_string(debugRand2) + "\nDMG-Factor: " + std::to_string(this->currentDMGfactor) +
                  "\nRand-Factor: " + std::to_string(this->currentRandomModifier));
    return debugReturn;
}

void Fighter::block() {
    this->blocking = true;
    this->sprite->setColor(COLOR_YELLOW);
}

Ability* Fighter::getAbility(int index) {
    return this->abilities[index];
}

Sprite* Fighter::getSprite() {
    return this->sprite;
}

void Fighter::heal() {
    this->currentHP = this->maxHP;
}

Fighter* Fighter::clone() {
    return new Fighter(this->getName(), this->getMaxHP(), this->getBaseDMG(), this->getBaseDEF(),
                        this->getBlockBonus(), this->getAbility(0), this->getAbility(1), this->getSprite()->clone());
}
