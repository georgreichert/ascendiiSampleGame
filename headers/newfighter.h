#ifndef NEWFIGHTER_H
#define NEWFIGHTER_H

#include "fightclub.h"

class NewFighter: public SubState {
    private:
        std::vector<Ability*> abilities;
        int cursorPosition = 0;

    public:
        NewFighter(Screen* screen, float start = 0.0f);
        ~NewFighter();
        void keyInput(int key);
        void update(int deltaTime);
};

#endif // NEWFIGHTER_H
