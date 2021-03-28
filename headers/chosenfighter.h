#ifndef CHOSENFIGHTER_H
#define CHOSENFIGHTER_H

#include "fightclub.h"

class ChosenFighter: public SubState {
    private:
        Fighter* fighter;
        OneVsOne* parentState;

    public:
        ChosenFighter(Screen* screen, OneVsOne* parentState, Fighter* fighter, float start = 0.0f);
        ~ChosenFighter();
        void keyInput(int key);
        void update(int deltaTime);
};

#endif // CHOSENFIGHTER_H
