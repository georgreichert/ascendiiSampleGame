#ifndef CHOOSEFIGHTER_H
#define CHOOSEFIGHTER_H

#include "fightclub.h"

class ChooseFighter: public SubState {
    private:
        std::vector<MenuElement*> menuElements;
        std::vector<Fighter*> fighters;
        int cursorPosition = 0;
        OneVsOne* parentState;

    public:
        ChooseFighter(Screen* screen, OneVsOne* parentState, float start = 0.0f);
        ~ChooseFighter();
        void keyInput(int key);
        void update(int deltaTime);
};

#endif // CHOOSEFIGHTER_H
