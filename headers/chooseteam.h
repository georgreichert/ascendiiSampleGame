#ifndef CHOOSETEAM_H
#define CHOOSETEAM_H

#include "fightclub.h"

class ChooseTeam: public SubState {
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
        TwoVsTwo* parentState;

    public:
        ChooseTeam(Screen* screen, TwoVsTwo* parentState, bool playerType = PLAYER_TYPE_AI, float start = 0.0f);
        ~ChooseTeam();
        void keyInput(int key);
        void update(int deltaTime);
        void toggleFocus();
        bool getPlayerType();
};

#endif // CHOOSETEAM_H
