#ifndef CHOOSEPLAYER_H
#define CHOOSEPLAYER_H

#include "fightclub.h"

class ChoosePlayer: public SubState {
    private:
        static const int numberOfMenuElements = 4;
        MenuElement* menuElements[numberOfMenuElements];
        Sprite* playerText;
        Sprite* aiText;
        Sprite* profilePic;
        Sprite* plusSign;
        Sprite* questionMark;
        int cursorPosition = 0;
        bool playerType;
        OneVsOne* parentState;

    public:
        ChoosePlayer(Screen* screen, OneVsOne* parentState, bool playerType = false, float start = 0.0f);
        ~ChoosePlayer();
        void keyInput(int key);
        void draw(int deltaTime);
        void toggleFocus();
        bool getPlayerType();
};

#endif // CHOOSEPLAYER_H
