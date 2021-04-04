#include "../headers/fightclub.h"

char DecisionTreeDefensive::decide(Fighter* fighter) {
    if (rand() % 3 > 0) {
        if (fighter->getCurrentHP() / fighter->getMaxHP() >= 0.75f) {
            if (fighter->getAbility(0)->getPower() >= fighter->getAbility(1)->getPower()) {
                return KEY_ABILITY_1;
            } else {
                return KEY_ABILITY_2;
            }
        } else {
            if (fighter->getAbility(0)->getDefense() >= fighter->getAbility(1)->getDefense()) {
                return KEY_ABILITY_1;
            } else {
                return KEY_ABILITY_2;
            }
        }
    } else {
        return KEY_BLOCK;
    }
}
